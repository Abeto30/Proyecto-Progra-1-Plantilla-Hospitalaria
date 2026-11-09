#include <iostream>
#include <limits>

#include "Menus/MenuEmpleado.h"
#include "Menus/GestionDepartamento.h"

using namespace std;

// Prototipo
void menu();

int main() {
    int opcion;

    GestorEmpleados gestor;
    GestorDepartamentos gestorDepartamentos;

    do {
        menu();

        if (!(cin >> opcion)) {
    cout << "Entrada invalida. Ingrese un numero." << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    continue;
 }

 cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                menuEmpleado(gestor);
                break;

            case 2:
                menuDepartamento(gestorDepartamentos);
                break;

            case 3:
                cout << "Gestion de puestos" << endl;
                break;

            case 4:
                cout << "Gestion de planilla" << endl;
                break;

            case 5:
                cout << "Consulta de comprobantes de pago" << endl;
                break;

            case 6:
                cout << "Guardar datos" << endl;
                break;

            case 7:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }

    } while (opcion != 7);

    return 0;
}

// Funcion para mostrar el menu
void menu() {
    cout << "\n==========================================" << endl;
    cout << " BIENVENIDO AL SISTEMA DE PLANILLA" << endl;
    cout << "==========================================" << endl;
    cout << "1. Gestionar empleados" << endl;
    cout << "2. Gestionar departamentos" << endl;
    cout << "3. Gestionar puestos" << endl;
    cout << "4. Gestionar planilla" << endl;
    cout << "5. Consultar comprobantes de pago" << endl;
    cout << "6. Guardar datos" << endl;
    cout << "7. Salir" << endl;
    cout << "==========================================" << endl;
    cout << "Ingrese una opcion: ";
}