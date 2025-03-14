// Created by NATSOFT Ronald Espitia.
#include <iostream>
#include <chrono>
#include <windows.h>
#include "utils.h"
#include <iomanip>

using namespace std;

// Función para mostrar la barra de progreso
void mostrarBarraProgreso(int progreso) {
    const int anchoBarra = 50; // Ancho de la barra de progreso
    cout << "[";
    int pos = anchoBarra * progreso / 100;
    for (int i = 0; i < anchoBarra; ++i) {
        if (i < pos) cout << "█";
        else if (i == pos) cout << ">";
        else cout << " ";
    }
    cout << "] " << setw(3) << progreso << " %\r";
    cout.flush(); // Forzar la salida inmediata
}

int main() {
    SetConsoleOutputCP(65001);
    cout << R"(
 _   _       _              __ _
| \ | | __ _| |_ ___  ___  / _| |_
|  \| |/ _` | __/ __|/ _ \| |_| __|
| |\  | (_| | |_\__ \ (_) |  _| |_
|_| \_|\__,_|\__|___/\___/|_|  \__|

Developed by Ronald Espitia ©
    )" << endl;

    // Mensajes de inicio
    cout << "■ Iniciando el proceso..." << endl;
    cout << endl;
    cout << "■ ARCHIVOS DE NOMINA" << endl;
    cout << endl;

    // Iniciar el cronómetro
    auto inicio = chrono::high_resolution_clock::now();

    // Número total de funciones a ejecutar
    const int totalFunciones = 8;

    // Ejecutar cada función y actualizar la barra de progreso
    for (int i = 0; i < totalFunciones; ++i) {
        // Ejecutar la función correspondiente
        switch (i) {
            case 0: exe1(); break;
            case 1: exe2(); break;
            case 2: exe3(); break;
            case 3: exe4(); break;
            case 4: exe5(); break;
            case 5: exe6(); break;
            case 6: exe7(); break;
            case 7: exe8(); break;
        }

        // Calcular el progreso
        int progreso = (i + 1) * 100 / totalFunciones;

        // Mostrar la barra de progreso
        mostrarBarraProgreso(progreso);
    }

    // Detener el cronómetro
    const auto fin = chrono::high_resolution_clock::now();

    // Calcular la duración en milisegundos
    const auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);

    // Convertir a segundos con decimales
    const double segundos = duracion.count() / 1000.0;

    // Imprimir el tiempo de ejecución
    cout << "\nTiempo de ejecución: " << segundos << " segundos" << endl;

    // Esperar a que el usuario presione ENTER para salir
    cout << "\n» Presione ENTER para salir...";
    cin.ignore(); // Limpiar el buffer de entrada
    //cin.get();    // Esperar a que el usuario presione ENTER

    return 0;
}
/*
#include <iostream>
#include <chrono>
#include <windows.h>
#include "utils.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    cout << R"(
         _   _       _              __ _
        | \ | | __ _| |_ ___  ___  / _| |_
        |  \| |/ _` | __/ __|/ _ \| |_| __|
        | |\  | (_| | |_\__ \ (_) |  _| |_
        |_| \_|\__,_|\__|___/\___/|_|  \__|

        Developed by Ronald Espitia ©
    )" << endl;

    // Mensajes de inicio
    cout << "■ Iniciando el proceso..." << endl;
    cout << endl;
    cout << "■ ARCHIVOS DE NOMINA" << endl;
    cout << endl;
    // Iniciar el cronómetro
    auto inicio = chrono::high_resolution_clock::now();

    exe1();
    exe2();
    exe3();
    exe4();
    exe5();
    exe6();
    exe7();
    exe8();

    // Detener el cronómetro
    const auto fin = chrono::high_resolution_clock::now();

    // Calcular la duración en milisegundos
    const auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);

    // Convertir a segundos con decimales
    const double segundos = duracion.count() / 1000.0;

    // Imprimir el tiempo de ejecución
    cout << "Tiempo de ejecución: " << segundos << " segundos" << endl;

}*/
