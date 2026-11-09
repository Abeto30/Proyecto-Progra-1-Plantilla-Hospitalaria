#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <sstream>
#include <cmath>
#include <cctype>

#include "MenuEmpleado.h"
#include "../Clases/Medico.h"
#include "../Clases/Enfermero.h"
#include "../Clases/Administrativo.h"
using namespace std;

// Funciones auxiliares
int leerEntero(const string& mensaje);
double leerDecimal(const string& mensaje);
string leerTexto(const string& mensaje);
string leerDato(const string& mensaje);

// Funciones del menu
void registrarEmpleado(GestorEmpleados& gestor);
void mostrarEmpleados(const GestorEmpleados& gestor);
void buscarEmpleado(GestorEmpleados& gestor);
void eliminarEmpleado(GestorEmpleados& gestor);
void cambiarEstadoEmpleado(GestorEmpleados& gestor);

// Leer enteros
int leerEntero(const string& mensaje) {
    string entrada;
    int valor;

    while (true) {
        cout << mensaje;

        if (!getline(cin, entrada)) {
            cout << "\nError al leer la entrada.\n";
            cin.clear();
            continue;
        }

        stringstream ss(entrada);
        char extra;

        if (ss >> valor && !(ss >> extra) && valor >= 0) {
            return valor;
        }

        cout << "Error: ingrese solamente un numero entero valido.\n";
    }
}

// Leer numeros decimales
double leerDecimal(const string& mensaje) {
    string entrada;
    double valor;

    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        stringstream ss(entrada);
        char extra;

        if (ss >> valor && !(ss >> extra) &&
            valor > 0 && isfinite(valor)) {
            return valor;
        }

        cout << "Error: ingrese un numero valido mayor que cero.\n";
    }
}

// Leer texto que contenga letras
string leerTexto(const string& mensaje) {
    string texto;
    bool tieneLetra;

    while (true) {
        cout << mensaje;
        getline(cin, texto);

        tieneLetra = false;

        for (unsigned char caracter : texto) {
            if (isalpha(caracter) || caracter >= 128) {
                tieneLetra = true;
                break;
            }
        }

        if (!texto.empty() && texto.find_first_not_of(" \t") != string::npos
            && tieneLetra) {
            return texto;
        }

        cout << "Error: este campo debe contener texto y no puede estar vacio.\n";
    }
}

// Leer identificacion, telefono y correo
// Permite numeros y caracteres especiales, pero no campos vacios.
string leerDato(const string& mensaje) {
    string dato;

    while (true) {
        cout << mensaje;
        getline(cin, dato);

        if (!dato.empty() &&
            dato.find_first_not_of(" \t") != string::npos) {
            return dato;
        }

        cout << "Error: este campo no puede estar vacio.\n";
    }
}

// Menu de empleados
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

        opcion = leerEntero("Seleccione una opcion: ");

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

    tipo = leerEntero("Tipo de empleado: ");

    if (tipo < 1 || tipo > 3) {
        cout << "Tipo de empleado invalido." << endl;
        return;
    }

    id = leerEntero("ID del empleado: ");

    if (id <= 0) {
        cout << "El ID debe ser mayor que cero." << endl;
        return;
    }

    if (gestor.buscarEmpleadoPorId(id) != nullptr) {
        cout << "Ya existe un empleado con ese ID." << endl;
        return;
    }

    nombre = leerTexto("Nombre completo: ");
    identificacion = leerDato("Identificacion: ");
    telefono = leerDato("Telefono: ");
    correo = leerDato("Correo: ");

    salarioBase = leerDecimal("Salario base: ");

    Empleado* nuevoEmpleado = nullptr;

    switch (tipo) {
        case 1:
            datoEspecifico = leerTexto("Especialidad del medico: ");

            nuevoEmpleado = new Medico(
                id, nombre, identificacion, telefono,
                correo, salarioBase, datoEspecifico
            );
            break;

        case 2:
            datoEspecifico = leerTexto("Turno del enfermero: ");

            nuevoEmpleado = new Enfermero(
                id, nombre, identificacion, telefono,
                correo, salarioBase, datoEspecifico
            );
            break;

        case 3:
            datoEspecifico = leerTexto("Cargo administrativo: ");

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

// Mostrar empleados
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

// Buscar empleado
void buscarEmpleado(GestorEmpleados& gestor) {
    int id = leerEntero("\nIngrese el ID del empleado: ");

    if (id <= 0) {
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
    cout << "Salario bruto: "
         << empleado->calcularSalarioBruto() << endl;

    cout << "Estado: "
         << (empleado->estaActivo() ? "Activo" : "Inactivo")
         << endl;
}

// Eliminar empleado
void eliminarEmpleado(GestorEmpleados& gestor) {
    int id = leerEntero("\nIngrese el ID del empleado que desea eliminar: ");

    if (id <= 0) {
        cout << "ID invalido." << endl;
        return;
    }

    if (gestor.eliminarEmpleadoPorId(id)) {
        cout << "Empleado eliminado correctamente." << endl;
    } else {
        cout << "No existe un empleado con ese ID." << endl;
    }
}

// Cambiar estado
void cambiarEstadoEmpleado(GestorEmpleados& gestor) {
    int id = leerEntero("\nIngrese el ID del empleado: ");

    if (id <= 0) {
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
//Menu empleado .cpp