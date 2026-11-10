
#include <iostream>

#include "Validacion General/Entrada.h"
#include "Menus/MenuEmpleado.h"
#include "Menus/GestionDepartamento.h"
#include "Menus/GestionPuesto.h"

using namespace std;

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
}

int main() {
    GestorEmpleados gestor;
    GestorDepartamentos gestorDepartamentos;

    int opcion;

    do {
        menu();

        opcion = leerEntero("Ingrese una opcion: ", 1, 7);

        switch (opcion) {
            case 1:
                menuEmpleado(gestor);
                break;

            case 2:
                menuDepartamento(gestorDepartamentos);
                break;

           case 3:
                menuPuesto(gestorDepartamentos);
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
        }

    } while (opcion != 7);

    return 0;
}
//Main.cpp