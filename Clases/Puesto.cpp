#include "Puesto.h"

Puesto::Puesto(int id, 
    const std::string& nombre, 
    const std::string& descripcion)

    : id(id), 
    nombre(nombre),
    descripcion(descripcion) {}

int Puesto::getId() const {
    return id;
}

std::string Puesto::getNombre() const {
    return nombre;
}

std::string Puesto::getDescripcion() const {
    return descripcion;
}

void Puesto::setNombre(const std::string& nombre) {
    this->nombre = nombre;
} 

void Puesto::setDescripcion(const std::string& descripcion) {
    this->descripcion = descripcion;
}
//Puesto.cpp