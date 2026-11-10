
#include <iostream>
#include <string>

#include "../Clases/Departamento.h"
#include "../Clases/Empleado.h"
#include "GestionDepartamento.h"
#include "../Validacion General/Entrada.h"

using namespace std;

// Funciones del menu
void registrarDepartamento(GestorDepartamentos& gestor);
void mostrarDepartamentos(const GestorDepartamentos& gestor);
void buscarDepartamento(GestorDepartamentos& gestor);

void eliminarDepartamento(
    GestorDepartamentos& gestor,
    GestorEmpleados& gestorEmpleados,
    GestorComprobantes& gestorComprobantes
);

// Menu de departamentos
void menuDepartamento(
    GestorDepartamentos& gestor,
    GestorEmpleados& gestorEmpleados,
    GestorComprobantes& gestorComprobantes
) {
    int opcion;

    do {
        cout << "\n===================================" << endl;
        cout << "      GESTION DE DEPARTAMENTOS" << endl;
        cout << "===================================" << endl;
        cout << "1. Registrar departamento" << endl;
        cout << "2. Mostrar departamentos" << endl;
        cout << "3. Buscar departamento por ID" << endl;
        cout << "4. Eliminar departamento" << endl;
        cout << "5. Consultar cantidad de departamentos" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "===================================" << endl;

        opcion = leerEntero("Seleccione una opcion: ", 0, 5);

        switch (opcion) {
            case 1:
                registrarDepartamento(gestor);
                break;

            case 2:
                mostrarDepartamentos(gestor);
                break;

            case 3:
                buscarDepartamento(gestor);
                break;

            case 4:
                eliminarDepartamento(
                    gestor,
                    gestorEmpleados,
                    gestorComprobantes
                );
                break;

            case 5:
                cout << "\nCantidad de departamentos: "
                     << gestor.getCantidadDepartamentos() << endl;
                break;

            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
        }

    } while (opcion != 0);
}

// Registrar departamento
void registrarDepartamento(GestorDepartamentos& gestor) {
    int id;
    string nombre;
    string descripcion;

    cout << "\n--- REGISTRO DE DEPARTAMENTO ---" << endl;

    id = leerEntero("ID del departamento: ", 1, 2147483647);

    if (gestor.buscarDepartamentoPorId(id) != nullptr) {
        cout << "Ya existe un departamento con ese ID." << endl;
        return;
    }

    nombre = leerLinea("Nombre del departamento: ");
    descripcion = leerLinea("Descripcion: ");

    Departamento* nuevo = new Departamento(id, nombre, descripcion);

    if (gestor.agregarDepartamento(nuevo)) {
        cout << "\nDepartamento registrado correctamente." << endl;
    } else {
        delete nuevo;
        cout << "No se pudo registrar el departamento." << endl;
    }
}

// Mostrar departamentos
void mostrarDepartamentos(const GestorDepartamentos& gestor) {
    int cantidad = gestor.getCantidadDepartamentos();

    if (cantidad == 0) {
        cout << "\nNo hay departamentos registrados." << endl;
        return;
    }

    cout << "\n========== DEPARTAMENTOS ==========" << endl;

    for (int i = 0; i < cantidad; i++) {
        Departamento* departamento =
            gestor.obtenerDepartamentoEnPosicion(i);

        if (departamento != nullptr) {
            cout << "\nID: " << departamento->getId() << endl;
            cout << "Nombre: " << departamento->getNombre() << endl;
            cout << "Descripcion: "
                 << departamento->getDescripcion() << endl;

            cout << "Cantidad de puestos: "
                 << departamento->getCantidadPuestos() << endl;

            cout << "-----------------------------------" << endl;
        }
    }
}

// Buscar departamento
void buscarDepartamento(GestorDepartamentos& gestor) {
    int id = leerEntero(
        "\nIngrese el ID del departamento: ",
        1,
        2147483647
    );

    Departamento* departamento =
        gestor.buscarDepartamentoPorId(id);

    if (departamento == nullptr) {
        cout << "No se encontro el departamento." << endl;
        return;
    }

    cout << "\nDepartamento encontrado:" << endl;
    cout << "ID: " << departamento->getId() << endl;
    cout << "Nombre: " << departamento->getNombre() << endl;
    cout << "Descripcion: "
         << departamento->getDescripcion() << endl;

    cout << "Cantidad de puestos: "
         << departamento->getCantidadPuestos() << endl;
}

// Eliminar departamento
void eliminarDepartamento(
    GestorDepartamentos& gestor,
    GestorEmpleados& gestorEmpleados,
    GestorComprobantes& gestorComprobantes
) {
    int id = leerEntero(
        "\nIngrese el ID del departamento que desea eliminar: ",
        1,
        2147483647
    );

    Departamento* departamento =
        gestor.buscarDepartamentoPorId(id);

    if (departamento == nullptr) {
        cout << "No existe un departamento con ese ID." << endl;
        return;
    }

    // Verificar si existen empleados asignados
    for (int i = 0; i < gestorEmpleados.getCantidadEmpleados(); i++) {
        Empleado* empleado =
            gestorEmpleados.obtenerEmpleadoEnPosicion(i);

        if (empleado != nullptr &&
            empleado->getDepartamento() == departamento) {

            cout << "\nNo se puede eliminar el departamento." << endl;
            cout << "Tiene empleados asignados." << endl;
            return;
        }
    }

    // Verificar si existen comprobantes asociados
    if (gestorComprobantes.tieneComprobanteParaDepartamento(id)) {
        cout << "\nNo se puede eliminar el departamento." << endl;
        cout << "Tiene comprobantes de pago asociados." << endl;
        cout << "Los registros historicos deben conservarse." << endl;
        return;
    }

    // Verificar si existen puestos registrados
    if (departamento->getCantidadPuestos() > 0) {
        cout << "\nNo se puede eliminar el departamento." << endl;
        cout << "Primero debe eliminar todos sus puestos." << endl;
        return;
    }

    if (gestor.eliminarDepartamentoPorId(id)) {
        cout << "Departamento eliminado correctamente." << endl;
    } else {
        cout << "No se pudo eliminar el departamento." << endl;
    }
}
