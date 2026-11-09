#include <iostream>
#include "Lista.h"

int main() {
    Lista<int> numeros;

    numeros.insertarFinal(10);
    numeros.insertarFinal(20);
    numeros.insertarInicio(5);

    std::cout << "Cantidad: " << numeros.getCantidad() << std::endl;

    for (int i = 0; i < numeros.getCantidad(); i++) {
        std::cout << numeros.obtener(i) << std::endl;
    }

    numeros.eliminar(1);

    std::cout << "Despues de eliminar:" << std::endl;

    for (int i = 0; i < numeros.getCantidad(); i++) {
        std::cout << numeros.obtener(i) << std::endl;
    }

    return 0;
}