#include <iostream>
#include <string>

#include "Validacion General/Entrada.h"
#include "Menus/MenuEmpleado.h"
#include "Menus/GestionDepartamento.h"
#include "Menus/GestionPuesto.h"
#include "Menus/GestionPlanilla.h"
#include "Gestores/GestorComprobantes.h"

#include "Persistencia/Almacenamiento.h"
#include "Persistencia/SerializadorDepartamentos.h"

using namespace std;

// Mostrar el menu principal
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

// Guardar los departamentos en el archivo
void guardarDepartamentos(
    AlmacenamientoArchivos& almacenamiento,
    const GestorDepartamentos& gestorDepartamentos) {

    string datos = SerializadorDepartamentos::serializar(
        gestorDepartamentos
    );

    if (almacenamiento.guardarDepartamentos(datos)) {
        cout << "Departamentos guardados correctamente." << endl;
    } else {
        cout << "Error al guardar los departamentos." << endl;
    }
}

int main() {

    GestorEmpleados gestor;
    GestorDepartamentos gestorDepartamentos;
    GestorComprobantes gestorComprobantes;

    AlmacenamientoArchivos almacenamiento;

    // Cargar departamentos al iniciar
    string datosDepartamentos;

    if (almacenamiento.cargarDepartamentos(datosDepartamentos)) {

        if (!datosDepartamentos.empty()) {

            if (SerializadorDepartamentos::deserializar(
                    datosDepartamentos,
                    gestorDepartamentos)) {

                cout << "Departamentos cargados correctamente." << endl;

            } else {
                cout << "Error: los datos de departamentos son invalidos."
                     << endl;
            }
        }

    } else {
        cout << "No se encontraron datos de departamentos guardados."
             << endl;
    }

    int opcion;

    do {
        menu();

        opcion = leerEntero("Ingrese una opcion: ", 1, 7);

        switch (opcion) {

            case 1:
                menuEmpleado(gestor, gestorDepartamentos);
                break;

            case 2:
                menuDepartamento(gestorDepartamentos, gestor);
                break;

            case 3:
                menuPuesto(gestorDepartamentos);
                break;

            case 4:
                menuPlanilla(gestor, gestorComprobantes);
                break;

            case 5:
                cout << "Consulta de comprobantes de pago" << endl;
                break;

            case 6:
                guardarDepartamentos(
                    almacenamiento,
                    gestorDepartamentos
                );
                break;

            case 7:
                guardarDepartamentos(
                    almacenamiento,
                    gestorDepartamentos
                );

                cout << "Saliendo del programa..." << endl;
                break;
        }

    } while (opcion != 7);

    return 0;
}