#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

#include "MenuEmpleado.h"
#include "../Medico.h"
#include "../Enfermero.h"
#include "../Administrativo.h"

using namespace std;

// Funciones auxiliares
bool leerEntero(const string& mensaje, int& valor);
bool leerDecimal(const string& mensaje, double& valor);
bool leerTexto(const string& mensaje, string& texto);

void registrarEmpleado(GestorEmpleados& gestor);
void mostrarEmpleados(const GestorEmpleados& gestor);
void buscarEmpleado(GestorEmpleados& gestor);
void eliminarEmpleado(GestorEmpleados& gestor);
void cambiarEstadoEmpleado(GestorEmpleados& gestor);

// Menu principal de empleados
void menuEmpleado(GestorEmpleados& gestor) {
    int opcion;

    do {
        cout << "\n===================================" << endl;
        cout << "       GESTION DE EMPLEADOS" << endl;
        cout << "===================================" << endl;
        cout << "1. Registrar empleado" << endl;
        cout << "2. Mostrar empleados" << endl;
        cout << "3. Buscar empleado por ID" << endl;
        cout << "4. Eliminar empleado" << endl;
        cout << "5. Consultar cantidad de empleados" << endl;
        cout << "6. Cambiar estado del empleado" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "===================================" << endl;

        if (!leerEntero("Seleccione una opcion: ", opcion)) {
            cout << "Entrada invalida." << endl;
            continue;
        }

        switch (opcion) {
            case 1:
                registrarEmpleado(gestor);
                break;

            case 2:
                mostrarEmpleados(gestor);
                break;

            case 3:
                buscarEmpleado(gestor);
                break;

            case 4:
                eliminarEmpleado(gestor);
                break;

            case 5:
                cout << "\nCantidad de empleados: "
                     << gestor.getCantidadEmpleados() << endl;
                break;

            case 6:
                cambiarEstadoEmpleado(gestor);
                break;

            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }

    } while (opcion != 0);
}

// Leer un numero entero
bool leerEntero(const string& mensaje, int& valor) {
    cout << mensaje;

    if (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    return true;
}

// Leer un numero decimal
bool leerDecimal(const string& mensaje, double& valor) {
    cout << mensaje;

    if (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }

    return true;
}

// Leer texto
string leerTexto(const string& mensaje) {
    string texto;

    do {
        cout << mensaje;
        getline(cin >> ws, texto);

        if (texto.empty()) {
            cout << "Error: este campo no puede estar vacio.\n";
        }

    } while (texto.empty());

    return texto;
}

// Registrar empleado
void registrarEmpleado(GestorEmpleados& gestor) {
    int tipo;
    int id;
    double salarioBase;

    string nombre;
    string identificacion;
    string telefono;
    string correo;
    string datoEspecifico;

    cout << "\n--- REGISTRO DE EMPLEADO ---" << endl;
    cout << "1. Medico" << endl;
    cout << "2. Enfermero" << endl;
    cout << "3. Administrativo" << endl;

    if (!leerEntero("Tipo de empleado: ", tipo)) {
        cout << "Entrada invalida." << endl;
        return;
    }

    if (tipo < 1 || tipo > 3) {
        cout << "Tipo de empleado invalido." << endl;
        return;
    }

    if (!leerEntero("ID del empleado: ", id) || id <= 0) {
        cout << "ID invalido." << endl;
        return;
    }

    if (gestor.buscarEmpleadoPorId(id) != nullptr) {
        cout << "Ya existe un empleado con ese ID." << endl;
        return;
    }

    if (!leerTexto("Nombre completo: ", nombre) ||
        !leerTexto("Identificacion: ", identificacion) ||
        !leerTexto("Telefono: ", telefono) ||
        !leerTexto("Correo: ", correo)) {
        cout << "Debe ingresar todos los datos." << endl;
        return;
    }

    if (!leerDecimal("Salario base: ", salarioBase) ||
        salarioBase <= 0) {
        cout << "Salario invalido." << endl;
        return;
    }

    Empleado* nuevoEmpleado = nullptr;

    switch (tipo) {
        case 1:
            if (!leerTexto("Especialidad del medico: ", datoEspecifico)) {
                cout << "Especialidad invalida." << endl;
                return;
            }

            nuevoEmpleado = new Medico(
                id, nombre, identificacion, telefono,
                correo, salarioBase, datoEspecifico
            );
            break;

        case 2:
            if (!leerTexto("Turno del enfermero: ", datoEspecifico)) {
                cout << "Turno invalido." << endl;
                return;
            }

            nuevoEmpleado = new Enfermero(
                id, nombre, identificacion, telefono,
                correo, salarioBase, datoEspecifico
            );
            break;

        case 3:
            if (!leerTexto("Cargo administrativo: ", datoEspecifico)) {
                cout << "Cargo invalido." << endl;
                return;
            }

            nuevoEmpleado = new Administrativo(
                id, nombre, identificacion, telefono,
                correo, salarioBase, datoEspecifico
            );
            break;
    }

    if (gestor.agregarEmpleado(nuevoEmpleado)) {
        cout << "\nEmpleado registrado correctamente." << endl;
    } else {
        delete nuevoEmpleado;
        cout << "No se pudo registrar el empleado." << endl;
    }
}

// Mostrar todos los empleados
void mostrarEmpleados(const GestorEmpleados& gestor) {
    int cantidad = gestor.getCantidadEmpleados();

    if (cantidad == 0) {
        cout << "\nNo hay empleados registrados." << endl;
        return;
    }

    cout << "\n========== LISTA DE EMPLEADOS ==========" << endl;

    for (int i = 0; i < cantidad; i++) {
        Empleado* empleado = gestor.obtenerEmpleadoEnPosicion(i);

        if (empleado != nullptr) {
            cout << "\nID: " << empleado->getId() << endl;
            cout << "Nombre: " << empleado->getNombre() << endl;
            cout << "Identificacion: " << empleado->getIdentificacion() << endl;
            cout << "Telefono: " << empleado->getTelefono() << endl;
            cout << "Correo: " << empleado->getCorreo() << endl;
            cout << "Tipo: " << empleado->getTipoEmpleado() << endl;

            cout << fixed << setprecision(2);
            cout << "Salario bruto: "
                 << empleado->calcularSalarioBruto() << endl;

            cout << "Estado: "
                 << (empleado->estaActivo() ? "Activo" : "Inactivo")
                 << endl;

            cout << "-----------------------------------" << endl;
        }
    }
}

// Buscar empleado por ID
void buscarEmpleado(GestorEmpleados& gestor) {
    int id;

    if (!leerEntero("\nIngrese el ID del empleado: ", id)) {
        cout << "ID invalido." << endl;
        return;
    }

    Empleado* empleado = gestor.buscarEmpleadoPorId(id);

    if (empleado == nullptr) {
        cout << "No se encontro el empleado." << endl;
        return;
    }

    cout << "\nEmpleado encontrado:" << endl;
    cout << "ID: " << empleado->getId() << endl;
    cout << "Nombre: " << empleado->getNombre() << endl;
    cout << "Identificacion: " << empleado->getIdentificacion() << endl;
    cout << "Telefono: " << empleado->getTelefono() << endl;
    cout << "Correo: " << empleado->getCorreo() << endl;
    cout << "Tipo: " << empleado->getTipoEmpleado() << endl;
    cout << "Salario bruto: " << empleado->calcularSalarioBruto() << endl;
    cout << "Estado: "
         << (empleado->estaActivo() ? "Activo" : "Inactivo") << endl;
}

// Eliminar empleado
void eliminarEmpleado(GestorEmpleados& gestor) {
    int id;

    if (!leerEntero("\nIngrese el ID del empleado que desea eliminar: ", id)) {
        cout << "ID invalido." << endl;
        return;
    }

    if (gestor.eliminarEmpleadoPorId(id)) {
        cout << "Empleado eliminado correctamente." << endl;
    } else {
        cout << "No existe un empleado con ese ID." << endl;
    }
}

// Cambiar estado del empleado
void cambiarEstadoEmpleado(GestorEmpleados& gestor) {
    int id;

    if (!leerEntero("\nIngrese el ID del empleado: ", id)) {
        cout << "ID invalido." << endl;
        return;
    }

    Empleado* empleado = gestor.buscarEmpleadoPorId(id);

    if (empleado == nullptr) {
        cout << "No se encontro el empleado." << endl;
        return;
    }

    empleado->setActivo(!empleado->estaActivo());

    cout << "Nuevo estado: "
         << (empleado->estaActivo() ? "Activo" : "Inactivo")
         << endl;
}