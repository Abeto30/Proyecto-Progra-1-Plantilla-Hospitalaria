#include "Entrada.h"

#include <iostream>
#include <limits>
#include <cctype>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <cstdlib>

using namespace std;

// Funciones auxiliares privadas
namespace
{
    string obtenerEntrada(const string& mensaje)
    {
        string valor;

        cout << mensaje;

        if (!getline(cin, valor))
        {
            throw runtime_error("Se finalizo la entrada de datos.");
        }

        return valor;
    }

    string limpiarEspacios(const string& valor)
    {
        size_t inicio = valor.find_first_not_of(" \t\r\n");

        if (inicio == string::npos)
        {
            return "";
        }

        size_t fin = valor.find_last_not_of(" \t\r\n");

        return valor.substr(inicio, fin - inicio + 1);
    }
}

// Limpia el estado de cin
void limpiarEntradaInvalida()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Lee una sola palabra
string leerToken(const string& mensaje)
{
    while (true)
    {
        string valor = limpiarEspacios(obtenerEntrada(mensaje));

        if (!valor.empty() &&
            valor.find_first_of(" \t\r\n") == string::npos)
        {
            return valor;
        }

        cout << "Entrada invalida. Ingrese una sola palabra."
             << endl;
    }
}

// Lee una linea completa
string leerLinea(const string& mensaje)
{
    while (true)
    {
        string valor = limpiarEspacios(obtenerEntrada(mensaje));

        if (!valor.empty())
        {
            return valor;
        }

        cout << "Este campo no puede estar vacio. Intente de nuevo."
             << endl;
    }
}

// Lee un numero entero dentro de un rango
int leerEntero(const string& mensaje, int minimo, int maximo)
{
    if (minimo > maximo)
    {
        throw invalid_argument("El rango de valores es invalido.");
    }

    while (true)
    {
        string entrada = obtenerEntrada(mensaje);
        stringstream ss(entrada);

        long long valor;
        ss >> ws;

        if (!(ss >> valor))
        {
            cout << "Entrada invalida. Debe ingresar un numero entero."
                 << endl;
            continue;
        }

        ss >> ws;

        if (!ss.eof())
        {
            cout << "Entrada invalida. No ingrese letras ni decimales."
                 << endl;
            continue;
        }

        if (valor < minimo || valor > maximo)
        {
            cout << "El valor debe estar entre "
                 << minimo << " y " << maximo
                 << ". Intente de nuevo." << endl;
            continue;
        }

        return static_cast<int>(valor);
    }
}

// Lee un numero decimal
double leerDouble(
    const string& mensaje,
    double minimo,
    bool estrictoMayor)
{
    if (!isfinite(minimo))
    {
        throw invalid_argument("El minimo debe ser un numero finito.");
    }

    while (true)
    {
        string entrada = obtenerEntrada(mensaje);
        stringstream ss(entrada);

        double valor;
        ss >> ws;

        if (!(ss >> valor))
        {
            cout << "Entrada invalida. Debe ingresar un numero."
                 << endl;
            continue;
        }

        ss >> ws;

        if (!ss.eof() || !isfinite(valor))
        {
            cout << "Entrada invalida. Ingrese un numero decimal valido."
                 << endl;
            continue;
        }

        if (estrictoMayor && valor <= minimo)
        {
            cout << "El valor debe ser mayor que "
                 << minimo << ". Intente de nuevo." << endl;
            continue;
        }

        if (!estrictoMayor && valor < minimo)
        {
            cout << "El valor no puede ser menor que "
                 << minimo << ". Intente de nuevo." << endl;
            continue;
        }

        return valor;
    }
}

// Lee una respuesta booleana
bool leerBooleano(const string& mensaje)
{
    cout << mensaje << endl;
    cout << "1. Si" << endl;
    cout << "0. No" << endl;

    int valor = leerEntero("Seleccione: ", 0, 1);

    return valor == 1;
}

void limpiarConsola()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausarConsola()
{
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}