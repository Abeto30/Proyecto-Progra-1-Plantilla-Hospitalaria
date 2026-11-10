
#include "GestorComprobantes.h"
#include <stdexcept>

// Constructor
GestorComprobantes::GestorComprobantes() {}

// Destructor
GestorComprobantes::~GestorComprobantes() {
    limpiarComprobantes();
}

// Agregar comprobante
bool GestorComprobantes::agregarComprobante(
    ComprobantePago* comprobante
) {
    if (comprobante == nullptr) {
        return false;
    }

    if (buscarComprobantePorId(comprobante->getId()) != nullptr) {
        return false;
    }

    comprobantes.insertarFinal(comprobante);
    return true;
}

// Buscar comprobante por ID
ComprobantePago* GestorComprobantes::buscarComprobantePorId(int id) const {
    for (int i = 0; i < comprobantes.getCantidad(); i++) {
        ComprobantePago* comprobante = comprobantes.obtener(i);

        if (comprobante != nullptr && comprobante->getId() == id) {
            return comprobante;
        }
    }

    return nullptr;
}

// Obtener cantidad de comprobantes
int GestorComprobantes::getCantidadComprobantes() const {
    return comprobantes.getCantidad();
}

// Obtener comprobante por posición
ComprobantePago* GestorComprobantes::obtenerComprobanteEnPosicion(
    int posicion
) const {
    if (posicion < 0 || posicion >= comprobantes.getCantidad()) {
        throw std::out_of_range("Posicion fuera de rango");
    }

    return comprobantes.obtener(posicion);
}

// Verificar si un empleado tiene comprobantes
bool GestorComprobantes::tieneComprobanteParaEmpleado(
    int empleadoId
) const {
    for (int i = 0; i < comprobantes.getCantidad(); i++) {
        ComprobantePago* comprobante = comprobantes.obtener(i);

        if (comprobante != nullptr &&
            comprobante->getEmpleadoId() == empleadoId) {
            return true;
        }
    }

    return false;
}

// Verificar si un departamento tiene comprobantes
bool GestorComprobantes::tieneComprobanteParaDepartamento(
    int departamentoId
) const {
    for (int i = 0; i < comprobantes.getCantidad(); i++) {
        ComprobantePago* comprobante = comprobantes.obtener(i);

        if (comprobante != nullptr &&
            comprobante->getDepartamentoId() == departamentoId) {
            return true;
        }
    }

    return false;
}

// Limpiar comprobantes
void GestorComprobantes::limpiarComprobantes() {
    while (!comprobantes.estaVacia()) {
        ComprobantePago* comprobante = comprobantes.obtener(0);

        delete comprobante;
        comprobantes.eliminar(0);
    }
}
