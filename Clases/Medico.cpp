#include "Medico.h"
#include <cmath>

// Validar textos
bool especialidadValida(const std::string& texto) {
    return !texto.empty() &&
           texto.find_first_not_of(" \t\n\r") != std::string::npos;
}

// Constructor
Medico::Medico(int id,
               const std::string& nombre,
               const std::string& identificacion,
               const std::string& telefono,
               const std::string& correo,
               double salarioBase,
               const std::string& especialidad)
    : Empleado(id, nombre, identificacion, telefono, correo, salarioBase),
      especialidad(especialidadValida(especialidad) ? especialidad : ""),
      horasExtras(0),
      horasGuardia(0),
      tarifaHoraExtra(0.0),
      tarifaHoraGuardia(0.0) {}

// Getter
std::string Medico::getEspecialidad() const {
    return especialidad;
}

// Setter
void Medico::setEspecialidad(const std::string& especialidad) {
    if (especialidadValida(especialidad)) {
        this->especialidad = especialidad;
    }
}

int Medico::getHorasExtras() const {
    return horasExtras;
}

int Medico::getHorasGuardia() const {
    return horasGuardia;
}

double Medico::getTarifaHoraExtra() const {
    return tarifaHoraExtra;
}

double Medico::getTarifaHoraGuardia() const {
    return tarifaHoraGuardia;
}

// Registrar horas extras
void Medico::registrarHorasExtras(int horas) {
    if (horas > 0 && horas <= 1000000 - horasExtras) {
        horasExtras += horas;
    }
}

// Registrar horas de guardia
void Medico::registrarHorasGuardia(int horas) {
    if (horas > 0 && horas <= 1000000 - horasGuardia) {
        horasGuardia += horas;
    }
}

// Calcular pagos adicionales
double Medico::calcularpagoHorasExtras() const {
    return horasExtras * tarifaHoraExtra;
}

double Medico::calcularpagoHorasGuardia() const {
    return horasGuardia * tarifaHoraGuardia;
}

// Métodos polimórficos
std::string Medico::getTipoEmpleado() const {
    return "Medico";
}

double Medico::calcularSalarioBruto() const {
    return getSalarioBase()
           + calcularpagoHorasExtras()
           + calcularpagoHorasGuardia();
}

// Configurar tarifas
void Medico::setTarifaHoraExtra(double tarifa) {
    if (std::isfinite(tarifa) && tarifa >= 0) {
        tarifaHoraExtra = tarifa;
    }
}

void Medico::setTarifaHoraGuardia(double tarifa) {
    if (std::isfinite(tarifa) && tarifa >= 0) {
        tarifaHoraGuardia = tarifa;
    }
}