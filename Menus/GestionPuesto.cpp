
#include <iostream>
#include <string>

#include "../Clases/Puesto.h"
#include "../Clases/Departamento.h"
#include "GestionPuesto.h"
#include "../Validacion General/Entrada.h"

using namespace std;

// Funciones del menu
void registrarPuesto(GestorDepartamentos& gestor);
void mostrarPuestos(const GestorDepartamentos& gestor);
void buscarPuesto(const GestorDepartamentos& gestor);
void eliminarPuesto(GestorDepartamentos& gestor);
void consultarCantidadPuestos(const GestorDepartamentos& gestor);

// Menu de puestos
void menuPuesto(GestorDepartamentos& gestor)
{
    int opcion;

    do
    {
        cout << "\n===================================" << endl;
        cout << "         GESTION DE PUESTOS" << endl;
        cout << "===================================" << endl;
        cout << "1. Registrar puesto" << endl;
        cout << "2. Mostrar puestos" << endl;
        cout << "3. Buscar puesto por ID" << endl;
        cout << "4. Eliminar puesto" << endl;
        cout << "5. Consultar cantidad de puestos" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "===================================" << endl;

        opcion = leerEntero("Seleccione una opcion: ", 0, 5);

        switch (opcion)
        {
            case 1:
                registrarPuesto(gestor);
                break;

            case 2:
                mostrarPuestos(gestor);
                break;

            case 3:
                buscarPuesto(gestor);
                break;

            case 4:
                eliminarPuesto(gestor);
                break;

            case 5:
                consultarCantidadPuestos(gestor);
                break;

            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
        }

    } while (opcion != 0);
}

// Registrar puesto
void registrarPuesto(GestorDepartamentos& gestor)
{
    if (gestor.getCantidadDepartamentos() == 0)
    {
        cout << "\nNo hay departamentos registrados." << endl;
        cout << "Debe registrar un departamento primero." << endl;
        return;
    }

    cout << "\n--- DEPARTAMENTOS DISPONIBLES ---" << endl;

    for (int i = 0; i < gestor.getCantidadDepartamentos(); i++)
    {
        Departamento* departamento =
            gestor.obtenerDepartamentoEnPosicion(i);

        if (departamento != nullptr)
        {
            cout << "ID: " << departamento->getId()
                 << " | Nombre: " << departamento->getNombre()
                 << endl;
        }
    }

    int idDepartamento = leerEntero(
        "\nIngrese el ID del departamento: ",
        1,
        2147483647
    );

    Departamento* departamento =
        gestor.buscarDepartamentoPorId(idDepartamento);

    if (departamento == nullptr)
    {
        cout << "No existe un departamento con ese ID." << endl;
        return;
    }

    int idPuesto = leerEntero(
        "ID del puesto: ",
        1,
        2147483647
    );

    // Verificar que el ID no este utilizado en ningun departamento
    for (int i = 0; i < gestor.getCantidadDepartamentos(); i++)
    {
        Departamento* actual =
            gestor.obtenerDepartamentoEnPosicion(i);

        if (actual != nullptr && actual->existePuestoID(idPuesto))
        {
            cout << "Ya existe un puesto con ese ID." << endl;
            return;
        }
    }

    string nombre = leerLinea("Nombre del puesto: ");
    string descripcion = leerLinea("Descripcion: ");

    Puesto nuevo(idPuesto, nombre, descripcion);

    if (departamento->agregarPuesto(nuevo))
    {
        cout << "\nPuesto registrado correctamente." << endl;
        cout << "Departamento: " << departamento->getNombre() << endl;
    }
    else
    {
        cout << "No se pudo registrar el puesto." << endl;
    }
}

// Mostrar todos los puestos
void mostrarPuestos(const GestorDepartamentos& gestor)
{
    int total = 0;

    for (int i = 0; i < gestor.getCantidadDepartamentos(); i++)
    {
        Departamento* departamento =
            gestor.obtenerDepartamentoEnPosicion(i);

        if (departamento != nullptr)
        {
            total += departamento->getCantidadPuestos();
        }
    }

    if (total == 0)
    {
        cout << "\nNo hay puestos registrados." << endl;
        return;
    }

    cout << "\n========== PUESTOS REGISTRADOS ==========" << endl;

    for (int i = 0; i < gestor.getCantidadDepartamentos(); i++)
    {
        Departamento* departamento =
            gestor.obtenerDepartamentoEnPosicion(i);

        if (departamento == nullptr ||
            departamento->getCantidadPuestos() == 0)
        {
            continue;
        }

        cout << "\nDepartamento: " << departamento->getNombre()
             << " (ID: " << departamento->getId() << ")" << endl;

        for (int j = 0; j < departamento->getCantidadPuestos(); j++)
        {
            Puesto puesto = departamento->obtenerPuestoEnPosicion(j);

            cout << "\nID del puesto: " << puesto.getId() << endl;
            cout << "Nombre: " << puesto.getNombre() << endl;
            cout << "Descripcion: " << puesto.getDescripcion() << endl;
            cout << "-----------------------------------" << endl;
        }
    }
}

// Buscar puesto por ID
void buscarPuesto(const GestorDepartamentos& gestor)
{
    int id = leerEntero(
        "\nIngrese el ID del puesto: ",
        1,
        2147483647
    );

    for (int i = 0; i < gestor.getCantidadDepartamentos(); i++)
    {
        Departamento* departamento =
            gestor.obtenerDepartamentoEnPosicion(i);

        if (departamento == nullptr)
        {
            continue;
        }

        for (int j = 0; j < departamento->getCantidadPuestos(); j++)
        {
            Puesto puesto = departamento->obtenerPuestoEnPosicion(j);

            if (puesto.getId() == id)
            {
                cout << "\nPuesto encontrado:" << endl;
                cout << "ID: " << puesto.getId() << endl;
                cout << "Nombre: " << puesto.getNombre() << endl;
                cout << "Descripcion: " << puesto.getDescripcion() << endl;
                cout << "Departamento: "
                     << departamento->getNombre() << endl;
                return;
            }
        }
    }

    cout << "No se encontro un puesto con ese ID." << endl;
}

// Eliminar puesto por ID
void eliminarPuesto(GestorDepartamentos& gestor)
{
    int id = leerEntero(
        "\nIngrese el ID del puesto que desea eliminar: ",
        1,
        2147483647
    );

    for (int i = 0; i < gestor.getCantidadDepartamentos(); i++)
    {
        Departamento* departamento =
            gestor.obtenerDepartamentoEnPosicion(i);

        if (departamento != nullptr &&
            departamento->eliminarPuestoID(id))
        {
            cout << "Puesto eliminado correctamente." << endl;
            cout << "Departamento: " << departamento->getNombre() << endl;
            return;
        }
    }

    cout << "No existe un puesto con ese ID." << endl;
}

// Consultar cantidad total de puestos
void consultarCantidadPuestos(const GestorDepartamentos& gestor)
{
    int total = 0;

    for (int i = 0; i < gestor.getCantidadDepartamentos(); i++)
    {
        Departamento* departamento =
            gestor.obtenerDepartamentoEnPosicion(i);

        if (departamento != nullptr)
        {
            total += departamento->getCantidadPuestos();
        }
    }

    cout << "\nCantidad total de puestos registrados: "
         << total << endl;
}
//GestionPuesto .cpp