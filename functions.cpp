// Created by NATSOFT Ronald Espitia.
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <future>
#include <algorithm>
using namespace std;

// Función para dividir una cadena en un vector de cadenas usando un delimitador
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Función para unir un vector de cadenas en una sola cadena usando un delimitador
string join(const vector<string>& tokens, char delimiter) {
    ostringstream result;
    for (size_t i = 0; i < tokens.size(); i++) {
        result << tokens[i];
        if (i < tokens.size() - 1) {
            result << delimiter;
        }
    }
    return result.str();
}

// Función principal
void functions(int colFileA, int newColumFileA, const string& fileB, int colFindB, int colResultB) {
    string fileA = "result.csv"; // Archivo principal (se modificará directamente)

    // Mapa para almacenar los valores de búsqueda y copia del fileB
    unordered_map<string, string> mapaBusqueda;

    // Leer el fileB y almacenar los valores en un mapa
    ifstream br(fileB);
    if (!br.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << fileB << endl;
        return;
    }

    string linea;
    while (getline(br, linea)) {
        vector<string> valores = split(linea, ';');
        if (valores.size() > colResultB) {
            string clave = valores[colFindB]; // Valor de búsqueda
            string valor = valores[colResultB]; // Valor a copiar
            mapaBusqueda[clave] = valor;
        }
    }
    br.close();

    // Leer el fileA y almacenar las líneas en una lista
    vector<string> lineas;
    string encabezado;
    ifstream brA(fileA);
    if (!brA.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << fileA << endl;
        return;
    }

    // Leer la primera fila (encabezado) y guardarla por separado
    getline(brA, encabezado);
    while (getline(brA, linea)) {
        lineas.push_back(linea); // Almacenar solo las filas de datos
    }
    brA.close();

    // Arreglo para almacenar las líneas procesadas en el orden original
    vector<string> lineasProcesadas(lineas.size());

    // Número de hilos (usamos el número de núcleos disponibles)
    unsigned int numHilos = thread::hardware_concurrency();
    vector<future<void>> futures;

    // Dividir las líneas en bloques para procesamiento concurrente
    int numLineas = lineas.size();
    int tamanoBloque = (numLineas + numHilos - 1) / numHilos; // Tamaño de cada bloque

    for (unsigned int i = 0; i < numHilos; i++) {
        int inicio = i * tamanoBloque;
        int fin = min(inicio + tamanoBloque, numLineas);

        // Verificar que el índice de inicio no sea mayor que el número de líneas
        if (inicio >= numLineas) {
            break; // Salir del bucle si no hay más líneas para procesar
        }

        // Crear una tarea para procesar el bloque de líneas
        futures.push_back(async(launch::async, [&, inicio, fin]() {
            for (int j = inicio; j < fin; j++) {
                string lin = lineas[j];
                vector<string> valores = split(lin, ';');
                if (valores.size() > newColumFileA) {
                    string clave = valores[colFileA]; // Valor de búsqueda en fileA
                    // Si hay coincidencia, copiar el valor al fileA
                    valores[newColumFileA] = mapaBusqueda.count(clave) ? mapaBusqueda[clave] : "errorXX";
                }
                // Reconstruir la línea actualizada y guardarla en la posición correcta
                lineasProcesadas[j] = join(valores, ';');
            }
        }));
    }

    // Esperar a que todas las tareas terminen
    for (auto& future : futures) {
        future.wait();
    }

    // Sobrescribir el fileA con el contenido actualizado
    ofstream fw(fileA);
    if (!fw.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << fileA << " para escritura" << endl;
        return;
    }

    // Escribir la primera fila (encabezado) sin modificaciones
    fw << encabezado << "\n";
    // Escribir las filas procesadas
    for (const string& linea : lineasProcesadas) {
        fw << linea << "\n";
    }
    fw.close();
}

// int main() {
//     // Ejemplo de uso
//     functions(0, 1, "fileB.csv", 0, 1);
//     return 0;
// }

