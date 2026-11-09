#include "GestorDepartamentos.h"
#include <stdexcept>

GestorDepartamentos::GestorDepartamentos() {}

GestorDepartamentos::~GestorDepartamentos() {
    limpiarDepartamentos();
}

// Agregar departamento
bool GestorDepartamentos::agregarDepartamento(Departamento* departamento) {

    if (departamento == nullptr) {
        return false;
    }

    if (buscarDepartamentoPorId(departamento->getId()) != nullptr) {
        return false;
    }

    departamentos.insertarFinal(departamento);

    return true;
}

// Buscar departamento por ID
Departamento* GestorDepartamentos::buscarDepartamentoPorId(int id) const {

    for (int i = 0; i < departamentos.getCantidad(); i++) {

        Departamento* departamento = departamentos.obtener(i);

        if (departamento != nullptr && departamento->getId() == id) {
            return departamento;
        }
    }

    return nullptr;
}

// Eliminar departamento por ID
bool GestorDepartamentos::eliminarDepartamentoPorId(int id) {

    for (int i = 0; i < departamentos.getCantidad(); i++) {

        Departamento* departamento = departamentos.obtener(i);

        if (departamento != nullptr && departamento->getId() == id) {

            delete departamento;
            departamentos.eliminar(i);

            return true;
        }
    }

    return false;
}

// Obtener cantidad de departamentos
int GestorDepartamentos::getCantidadDepartamentos() const {
    return departamentos.getCantidad();
}

// Limpiar departamentos
void GestorDepartamentos::limpiarDepartamentos() {

    while (!departamentos.estaVacia()) {

        Departamento* departamento = departamentos.obtener(0);

        delete departamento;
        departamentos.eliminar(0);
    }
}

// Obtener departamento por posición
Departamento* GestorDepartamentos::obtenerDepartamentoEnPosicion(int posicion) const {

    if (posicion < 0 || posicion >= departamentos.getCantidad()) {
        throw std::out_of_range("Posicion fuera de rango");
    }

    return departamentos.obtener(posicion);
}