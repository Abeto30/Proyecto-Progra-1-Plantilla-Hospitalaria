#include <iostream>
#include "../Validacion General/Entrada.h"

using namespace std;

int main()
{
    cout << "===== PRUEBA DEL MODULO DE ENTRADA =====\n\n";

    string nombre = leerLinea("Ingrese su nombre: ");

    int edad = leerEntero("Ingrese su edad (18-100): ", 18, 100);

    double salario = leerDouble("Ingrese un salario mayor que 0: ", 0, true);

    bool activo = leerBooleano("¿El empleado esta activo?");

    cout << "\n===== RESULTADOS =====\n";
    cout << "Nombre: " << nombre << endl;
    cout << "Edad: " << edad << endl;
    cout << "Salario: " << salario << endl;
    cout << "Activo: " << (activo ? "Si" : "No") << endl;

    return 0;
}