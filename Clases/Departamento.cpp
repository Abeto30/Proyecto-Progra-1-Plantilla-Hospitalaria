#include "Departamento.h"

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

void Departamento::agregarPuesto(const Puesto& puesto) {
    puestos.insertarFinal(puesto);
}

int Departamento::getCantidadPuestos() const {
    return puestos.getCantidad();
}
//Departamento.cpp