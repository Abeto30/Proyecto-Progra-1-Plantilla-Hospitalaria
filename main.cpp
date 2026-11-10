
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
#include "Persistencia/SerializadorEmpleados.h"
#include "Persistencia/SerializadorPlanilla.h"

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

// Guardar departamentos
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

// Guardar empleados
void guardarEmpleados(
    AlmacenamientoArchivos& almacenamiento,
    const GestorEmpleados& gestorEmpleados) {

    string datos = SerializadorEmpleados::serializar(
        gestorEmpleados
    );

    if (almacenamiento.guardarEmpleados(datos)) {
        cout << "Empleados guardados correctamente." << endl;
    } else {
        cout << "Error al guardar los empleados." << endl;
    }
}

// Guardar comprobantes de pago
void guardarPlanilla(
    AlmacenamientoArchivos& almacenamiento,
    const GestorComprobantes& gestorComprobantes) {

    string datos = SerializadorPlanilla::serializar(
        gestorComprobantes
    );

    if (almacenamiento.guardarPlanilla(datos)) {
        cout << "Comprobantes de pago guardados correctamente." << endl;
    } else {
        cout << "Error al guardar los comprobantes de pago." << endl;
    }
}

// Guardar todos los datos
void guardarDatos(
    AlmacenamientoArchivos& almacenamiento,
    const GestorDepartamentos& gestorDepartamentos,
    const GestorEmpleados& gestorEmpleados,
    const GestorComprobantes& gestorComprobantes) {

    guardarDepartamentos(almacenamiento, gestorDepartamentos);
    guardarEmpleados(almacenamiento, gestorEmpleados);
    guardarPlanilla(almacenamiento, gestorComprobantes);
}

int main() {

    GestorEmpleados gestor;
    GestorDepartamentos gestorDepartamentos;
    GestorComprobantes gestorComprobantes;

    AlmacenamientoArchivos almacenamiento;

    // Cargar departamentos primero
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

    // Cargar empleados después de los departamentos
    string datosEmpleados;

    if (almacenamiento.cargarEmpleados(datosEmpleados)) {

        if (!datosEmpleados.empty()) {

            if (SerializadorEmpleados::deserializar(
                    datosEmpleados,
                    gestor,
                    gestorDepartamentos)) {

                cout << "Empleados cargados correctamente." << endl;

            } else {
                cout << "Error: los datos de empleados son invalidos."
                     << endl;
            }
        }

    } else {
        cout << "No se encontraron datos de empleados guardados."
             << endl;
    }

    // Cargar comprobantes de pago
    string datosPlanilla;

    if (almacenamiento.cargarPlanilla(datosPlanilla)) {

        if (!datosPlanilla.empty()) {

            if (SerializadorPlanilla::deserializar(
                    datosPlanilla,
                    gestorComprobantes)) {

                cout << "Comprobantes de pago cargados correctamente."
                     << endl;

            } else {
                cout << "Error: los datos de planilla son invalidos."
                     << endl;
            }
        }

    } else {
        cout << "No se encontraron comprobantes guardados." << endl;
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
                guardarDatos(
                    almacenamiento,
                    gestorDepartamentos,
                    gestor,
                    gestorComprobantes
                );
                break;

            case 7:
                guardarDatos(
                    almacenamiento,
                    gestorDepartamentos,
                    gestor,
                    gestorComprobantes
                );

                cout << "Saliendo del programa..." << endl;
                break;
        }

    } while (opcion != 7);

    return 0;
}
