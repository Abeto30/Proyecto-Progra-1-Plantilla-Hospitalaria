#include "Departamento.h"
#include <stdexcept>

Departamento::Departamento(int id,
                           const std::string& nombre,
                           const std::string& descripcion)
    : id(id),
      nombre(nombre),
      descripcion(descripcion) {}

int Departamento::getId() const {
    return id;
}

std::string Departamento::getNombre() const {
    return nombre;
}

std::string Departamento::getDescripcion() const {
    return descripcion;
}

void Departamento::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Departamento::setDescripcion(const std::string& descripcion) {
    this->descripcion = descripcion;
}

bool Departamento::agregarPuesto(const Puesto& puesto) {
    if (existePuestoID(puesto.getId())) {
        return false;
    }

    puestos.insertarFinal(puesto);
    return true;
}

bool Departamento::existePuestoID(int id) const {
    for (int i = 0; i < puestos.getCantidad(); i++) {
        if (puestos.obtener(i).getId() == id) {
            return true;
        }
    }

    return false;
}

bool Departamento::eliminarPuestoID(int id) {
    for (int i = 0; i < puestos.getCantidad(); i++) {
        if (puestos.obtener(i).getId() == id) {
            return puestos.eliminar(i);
        }
    }

    return false;
}

Puesto Departamento::obtenerPuestoEnPosicion(int posicion) const {
    if (posicion < 0 || posicion >= puestos.getCantidad()) {
        throw std::out_of_range("Posicion fuera de rango");
    }

    return puestos.obtener(posicion);
}

int Departamento::getCantidadPuestos() const {
    return puestos.getCantidad();
}
//Departamento .cpp