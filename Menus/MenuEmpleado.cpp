#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

#include "MenuEmpleado.h"
#include "../Clases/Medico.h"
#include "../Clases/Enfermero.h"
#include "../Clases/Administrativo.h"
#include "../Clases/Departamento.h"
#include "../Validacion General/Entrada.h"
#include "../Gestores/GestorComprobantes.h"

using namespace std;

// Funciones auxiliares
string leerTexto(const string& mensaje);
string leerDato(const string& mensaje);
bool correoValido(const string& correo);
string leerCorreo(const string& mensaje);

// Funciones del menu
void registrarEmpleado(
    GestorEmpleados& gestor,
    GestorDepartamentos& gestorDepartamentos
);

void mostrarEmpleados(const GestorEmpleados& gestor);
void buscarEmpleado(GestorEmpleados& gestor);

void eliminarEmpleado(
    GestorEmpleados& gestor,
    GestorComprobantes& gestorComprobantes
);

void cambiarEstadoEmpleado(GestorEmpleados& gestor);

// Leer texto que contenga letras
string leerTexto(const string& mensaje) {
    string texto;

    while (true) {
        cout << mensaje;
        getline(cin, texto);

        bool tieneLetra = false;

        for (unsigned char caracter : texto) {
            if (isalpha(caracter) || caracter >= 128) {
                tieneLetra = true;
                break;
            }
        }

        if (!texto.empty() &&
            texto.find_first_not_of(" \t") != string::npos &&
            tieneLetra) {
            return texto;
        }

        cout << "Error: este campo debe contener texto y no puede estar vacio.\n";
    }
}

// Leer identificacion y telefono
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

// Validar formato basico de correo electronico
bool correoValido(const string& correo) {
    size_t arroba = correo.find('@');
    size_t punto = correo.find('.', arroba);

    return arroba != string::npos &&
           punto != string::npos &&
           arroba > 0 &&
           punto > arroba + 1 &&
           punto < correo.length() - 1;
}

// Leer correo electronico validado
string leerCorreo(const string& mensaje) {
    string correo;

    while (true) {
        cout << mensaje;
        getline(cin, correo);

        size_t inicio = correo.find_first_not_of(" \t\r\n");

        if (inicio != string::npos) {
            size_t fin = correo.find_last_not_of(" \t\r\n");
            correo = correo.substr(inicio, fin - inicio + 1);
        }

        if (correoValido(correo)) {
            return correo;
        }

        cout << "Error: ingrese un correo electronico valido.\n";
    }
}

// Menu de empleados
void menuEmpleado(
    GestorEmpleados& gestor,
    GestorDepartamentos& gestorDepartamentos,
    GestorComprobantes& gestorComprobantes
) {
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

        opcion = leerEntero("Seleccione una opcion: ", 0, 6);

        switch (opcion) {
            case 1:
                registrarEmpleado(gestor, gestorDepartamentos);
                break;

            case 2:
                mostrarEmpleados(gestor);
                break;

            case 3:
                buscarEmpleado(gestor);
                break;

            case 4:
                eliminarEmpleado(gestor, gestorComprobantes);
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
        }

    } while (opcion != 0);
}

// Registrar empleado
void registrarEmpleado(
    GestorEmpleados& gestor,
    GestorDepartamentos& gestorDepartamentos
) {
    int tipo;
    int id;
    int idDepartamento;
    double salarioBase;

    string nombre;
    string identificacion;
    string telefono;
    string correo;
    string datoEspecifico;

    if (gestorDepartamentos.getCantidadDepartamentos() == 0) {
        cout << "\nNo hay departamentos registrados." << endl;
        cout << "Debe registrar un departamento primero." << endl;
        return;
    }

    cout << "\n--- DEPARTAMENTOS DISPONIBLES ---" << endl;

    for (int i = 0; i < gestorDepartamentos.getCantidadDepartamentos(); i++) {
        Departamento* departamento =
            gestorDepartamentos.obtenerDepartamentoEnPosicion(i);

        if (departamento != nullptr) {
            cout << "ID: " << departamento->getId()
                 << " | Nombre: " << departamento->getNombre()
                 << endl;
        }
    }

    idDepartamento = leerEntero(
        "\nIngrese el ID del departamento: ",
        1,
        2147483647
    );

    Departamento* departamento =
        gestorDepartamentos.buscarDepartamentoPorId(idDepartamento);

    if (departamento == nullptr) {
        cout << "No existe un departamento con ese ID." << endl;
        return;
    }

    cout << "\n--- REGISTRO DE EMPLEADO ---" << endl;
    cout << "1. Medico" << endl;
    cout << "2. Enfermero" << endl;
    cout << "3. Administrativo" << endl;

    tipo = leerEntero("Tipo de empleado: ", 1, 3);

    id = leerEntero("ID del empleado: ", 1, 2147483647);

    if (gestor.buscarEmpleadoPorId(id) != nullptr) {
        cout << "Ya existe un empleado con ese ID." << endl;
        return;
    }

    nombre = leerTexto("Nombre completo: ");
    identificacion = leerDato("Identificacion: ");
    telefono = leerDato("Telefono: ");
    correo = leerCorreo("Correo: ");

    salarioBase = leerDouble("Salario base: ", 0, true);

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

    nuevoEmpleado->setDepartamento(departamento);

    if (gestor.agregarEmpleado(nuevoEmpleado)) {
        cout << "\nEmpleado registrado correctamente." << endl;
        cout << "Departamento asignado: "
             << departamento->getNombre() << endl;
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

            Departamento* departamento = empleado->getDepartamento();

            cout << "Departamento: "
                 << (departamento != nullptr
                     ? departamento->getNombre()
                     : "Sin asignar") << endl;

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
    int id = leerEntero("\nIngrese el ID del empleado: ", 1, 2147483647);

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

    Departamento* departamento = empleado->getDepartamento();

    cout << "Departamento: "
         << (departamento != nullptr
             ? departamento->getNombre()
             : "Sin asignar") << endl;

    cout << "Salario bruto: "
         << empleado->calcularSalarioBruto() << endl;

    cout << "Estado: "
         << (empleado->estaActivo() ? "Activo" : "Inactivo")
         << endl;
}

// Eliminar empleado
void eliminarEmpleado(
    GestorEmpleados& gestor,
    GestorComprobantes& gestorComprobantes
) {
    int id = leerEntero(
        "\nIngrese el ID del empleado que desea eliminar: ",
        1,
        2147483647
    );

    Empleado* empleado = gestor.buscarEmpleadoPorId(id);

    if (empleado == nullptr) {
        cout << "No existe un empleado con ese ID." << endl;
        return;
    }

    if (gestorComprobantes.tieneComprobanteParaEmpleado(id)) {
        cout << "\nNo se puede eliminar el empleado." << endl;
        cout << "Tiene comprobantes de pago asociados." << endl;
        cout << "Los registros historicos deben conservarse." << endl;
        return;
    }

    if (gestor.eliminarEmpleadoPorId(id)) {
        cout << "Empleado eliminado correctamente." << endl;
    } else {
        cout << "No se pudo eliminar el empleado." << endl;
    }
}

// Cambiar estado
void cambiarEstadoEmpleado(GestorEmpleados& gestor) {
    int id = leerEntero("\nIngrese el ID del empleado: ", 1, 2147483647);

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

// Menu empleado .cpp
