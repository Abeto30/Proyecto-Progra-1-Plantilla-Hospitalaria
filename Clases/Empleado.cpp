#include "Empleado.h"
#include <cmath>

// Verificar que un texto no esté vacío ni contenga solamente espacios
bool textoValido(const std::string& texto) {
    return !texto.empty() &&
           texto.find_first_not_of(" \t\n\r") != std::string::npos;
}

// Constructor
Empleado::Empleado(int id,
                   const std::string& nombre,
                   const std::string& identificacion,
                   const std::string& telefono,
                   const std::string& correo,
                   double salarioBase)
    : id(id),
      nombre(textoValido(nombre) ? nombre : ""),
      identificacion(textoValido(identificacion) ? identificacion : ""),
      telefono(textoValido(telefono) ? telefono : ""),
      correo(textoValido(correo) ? correo : ""),
      salarioBase(std::isfinite(salarioBase) && salarioBase >= 0
                      ? salarioBase : 0),
      activo(true) {
}

// Destructor
Empleado::~Empleado() {}

// Getters
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

// Setters
void Empleado::setNombre(const std::string& nombre) {
    if (textoValido(nombre)) {
        this->nombre = nombre;
    }
}

void Empleado::setIdentificacion(const std::string& identificacion) {
    if (textoValido(identificacion)) {
        this->identificacion = identificacion;
    }
}

void Empleado::setTelefono(const std::string& telefono) {
    if (textoValido(telefono)) {
        this->telefono = telefono;
    }
}

void Empleado::setCorreo(const std::string& correo) {
    if (textoValido(correo)) {
        std::size_t arroba = correo.find('@');
        std::size_t punto = correo.find('.', arroba);

        if (arroba != std::string::npos &&
            punto != std::string::npos &&
            arroba > 0 &&
            punto > arroba + 1 &&
            punto < correo.length() - 1) {

            this->correo = correo;
        }
    }
}

void Empleado::setSalarioBase(double salarioBase) {
    if (std::isfinite(salarioBase) && salarioBase >= 0) {
        this->salarioBase = salarioBase;
    }
}

void Empleado::setActivo(bool activo) {
    this->activo = activo;
}