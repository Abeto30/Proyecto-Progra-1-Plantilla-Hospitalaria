#include "Empleado.h"

Empleado::Empleado(int id,
                   const std::string& nombre,
                   const std::string& identificacion,
                   const std::string& telefono,
                   const std::string& correo,
                   double salarioBase)
    : id(id),
      nombre(nombre),
      identificacion(identificacion),
      telefono(telefono),
      correo(correo),
      salarioBase(salarioBase),
      activo(true) {
}

// Destructor
Empleado::~Empleado() {}

// Inicio de los get
int Empleado::getId() const {
    return id;
}

std::string Empleado::getNombre() const {
    return nombre;
}

std::string Empleado::getIdentificacion() const {
    return identificacion;
}

std::string Empleado::getTelefono() const {
    return telefono;
}

std::string Empleado::getCorreo() const {
    return correo;
}

double Empleado::getSalarioBase() const {
    return salarioBase;
}

bool Empleado::estaActivo() const {
    return activo;
}
// Fin de los get

// Inicio de los set
void Empleado::setNombre(const std::string& nombre) {
    this->nombre = nombre;
}

void Empleado::setIdentificacion(const std::string& identificacion) {
    this->identificacion = identificacion;
}

void Empleado::setTelefono(const std::string& telefono) {
    this->telefono = telefono;
}

void Empleado::setCorreo(const std::string& correo) {
    this->correo = correo;
}

void Empleado::setSalarioBase(double salarioBase) {
    if (salarioBase >= 0) {
        this->salarioBase = salarioBase;
    }
}

void Empleado::setActivo(bool activo) {
    this->activo = activo;
}
// Fin de los set
//Emplado.cpp