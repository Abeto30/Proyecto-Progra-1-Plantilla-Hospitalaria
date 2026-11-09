#include <iostream>
#include <limits>
#include "MenuEmpleado.h"

using namespace std;

void menuEmpleado(GestorEmpleados& gestor) {
    int opcion;

    do {
        cout << "\n--- Menu de Gestion de Empleados ---" << endl;
        cout << "1. Agregar empleado" << endl;
        cout << "2. Mostrar empleado" << endl;
        cout << "3. Buscar por ID" << endl;
        cout << "4. Eliminar empleado" << endl;
        cout << "5. Consultar cantidad de empleados" << endl;
        cout << "6. Volver al menu principal" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Ingrese un numero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
            case 1:
                gestor.agregarEmpleado();
                break;

            case 2:
                gestor.modificarEmpleado();
                break;

            case 3:
                gestor.eliminarEmpleado();
                break;

            case 4:
                gestor.listarEmpleados();
                break;

            case 5:
                cout << "Volviendo al menu principal..." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }

    } while (opcion != 5);
}