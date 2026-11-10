#include "Departamento.h"
#include <stdexcept>
// Constructor
Departamento::Departamento(
    int id,
    const std::string& nombre,
    const std::string& descripcion
)
    : id(id),
      nombre(nombre),
      descripcion(descripcion) {}

// Obtener ID
int Departamento::getId() const {
    return id;
}

// Obtener nombre
std::string Departamento::getNombre() const {
    return nombre;
}

// Obtener descripcion
std::string Departamento::getDescripcion() const {
    return descripcion;
}

// Modificar nombre
void Departamento::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

// Modificar descripcion
void Departamento::setDescripcion(const std::string& descripcion) {
    this->descripcion = descripcion;
}

// Agregar puesto
bool Departamento::agregarPuesto(const Puesto& puesto) {
    if (existePuestoID(puesto.getId())) {
        return false;
    }

    puestos.insertarFinal(puesto);
    return true;
}

// Comprobar si existe un puesto
bool Departamento::existePuestoID(int id) const {
    for (int i = 0; i < puestos.getCantidad(); i++) {
        if (puestos.obtener(i).getId() == id) {
            return true;
        }
    }

    return false;
}

// Eliminar puesto
bool Departamento::eliminarPuestoID(int id) {
    for (int i = 0; i < puestos.getCantidad(); i++) {
        if (puestos.obtener(i).getId() == id) {
            puestos.eliminar(i);
            return true;
        }
    }

    return false;
}

// Obtener puesto por posicion
Puesto Departamento::obtenerPuestoEnPosicion(int posicion) const {
    if (posicion < 0 || posicion >= puestos.getCantidad()) {
        throw std::out_of_range("Posicion fuera de rango");
    }

    return puestos.obtener(posicion);
}

// Obtener cantidad de puestos
int Departamento::getCantidadPuestos() const {
    return puestos.getCantidad();
}
