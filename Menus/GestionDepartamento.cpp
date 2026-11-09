#include <iostream>
#include <string>
#include <sstream>
#include "../Departamento.h"
#include "GestionDepartamento.h"

using namespace std;

// Funciones auxiliares
int leerEnteroDepartamento(const string& mensaje);
string leerTextoDepartamento(const string& mensaje);

// Funciones del menu
void registrarDepartamento(GestorDepartamentos& gestor);
void mostrarDepartamentos(const GestorDepartamentos& gestor);
void buscarDepartamento(GestorDepartamentos& gestor);
void eliminarDepartamento(GestorDepartamentos& gestor);

// Leer enteros
int leerEnteroDepartamento(const string& mensaje) {
    string entrada;
    int valor;

    while (true) {
        cout << mensaje;
        getline(cin, entrada);

        stringstream ss(entrada);
        char extra;

        if (ss >> valor && !(ss >> extra) && valor >= 0) {
            return valor;
        }

        cout << "Error: ingrese un numero entero valido.\n";
    }
}

// Leer texto
string leerTextoDepartamento(const string& mensaje) {
    string texto;

    while (true) {
        cout << mensaje;
        getline(cin, texto);

        if (!texto.empty() &&
            texto.find_first_not_of(" \t") != string::npos) {
            return texto;
        }

        cout << "Error: este campo no puede estar vacio.\n";
    }
}

// Menu de departamentos
void menuDepartamento(GestorDepartamentos& gestor) {
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

        opcion = leerEnteroDepartamento("Seleccione una opcion: ");

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
                eliminarDepartamento(gestor);
                break;

            case 5:
                cout << "\nCantidad de departamentos: "
                     << gestor.getCantidadDepartamentos() << endl;
                break;

            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
        }

    } while (opcion != 0);
}

// Registrar departamento
void registrarDepartamento(GestorDepartamentos& gestor) {
    int id;
    string nombre;
    string descripcion;

    cout << "\n--- REGISTRO DE DEPARTAMENTO ---" << endl;

    id = leerEnteroDepartamento("ID del departamento: ");

    if (id <= 0) {
        cout << "El ID debe ser mayor que cero." << endl;
        return;
    }

    if (gestor.buscarDepartamentoPorId(id) != nullptr) {
        cout << "Ya existe un departamento con ese ID." << endl;
        return;
    }

    nombre = leerTextoDepartamento("Nombre del departamento: ");
    descripcion = leerTextoDepartamento("Descripcion: ");

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
    int id = leerEnteroDepartamento(
        "\nIngrese el ID del departamento: "
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
void eliminarDepartamento(GestorDepartamentos& gestor) {
    int id = leerEnteroDepartamento(
        "\nIngrese el ID del departamento que desea eliminar: "
    );

    if (id <= 0) {
        cout << "ID invalido." << endl;
        return;
    }

    if (gestor.eliminarDepartamentoPorId(id)) {
        cout << "Departamento eliminado correctamente." << endl;
    } else {
        cout << "No existe un departamento con ese ID." << endl;
    }
}