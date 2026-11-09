#include "GestorEmpleados.h"
#include <stdexcept>

GestorEmpleados::GestorEmpleados() {}

GestorEmpleados::~GestorEmpleados() {
    limpiarEmpleados();
}

// Agregar un empleado
bool GestorEmpleados::agregarEmpleado(Empleado* empleado) {
    if (empleado == nullptr) {
        return false;
    }

    if (buscarEmpleadoPorId(empleado->getId()) != nullptr) {
        return false;
    }

    empleados.insertarFinal(empleado);
    return true;
}

// Buscar un empleado por ID
Empleado* GestorEmpleados::buscarEmpleadoPorId(int id) const {
    for (int i = 0; i < empleados.getCantidad(); ++i) {
        Empleado* empleado = empleados.obtener(i);

        if (empleado != nullptr && empleado->getId() == id) {
            return empleado;
        }
    }

    return nullptr;
}

// Eliminar un empleado por ID
bool GestorEmpleados::eliminarEmpleadoPorId(int id) {
    for (int i = 0; i < empleados.getCantidad(); ++i) {
        Empleado* empleado = empleados.obtener(i);

        if (empleado != nullptr && empleado->getId() == id) {
            delete empleado;
            empleados.eliminar(i);
            return true;
        }
    }

    return false;
}

// Obtener cantidad de empleados
int GestorEmpleados::getCantidadEmpleados() const {
    return empleados.getCantidad();
}

// Consultar si un empleado está activo
bool GestorEmpleados::estaEmpleadoActivo(int id) const {
    Empleado* empleado = buscarEmpleadoPorId(id);

    if (empleado != nullptr) {
        return empleado->estaActivo();
    }

    return false;
}

// Limpiar la lista de empleados
void GestorEmpleados::limpiarEmpleados() {
    while (!empleados.estaVacia()) {
        Empleado* empleado = empleados.obtener(0);
        delete empleado;
        empleados.eliminar(0);
    }
}

// Obtener empleado en una posición específica
Empleado* GestorEmpleados::obtenerEmpleadoEnPosicion(int posicion) const {
    if (posicion < 0 || posicion >= empleados.getCantidad()) {
        throw std::out_of_range("Posición fuera de rango");
    }

    return empleados.obtener(posicion);
}