#include "Medico.h"

Medico::Medico(int id,
               const std::string& nombre,
               const std::string& identificacion,
               const std::string& telefono,
               const std::string& correo,
               double salarioBase,
               const std::string& especialidad)
    : Empleado(id, nombre, identificacion, telefono, correo, salarioBase),
      especialidad(especialidad),
      horasExtras(0),
      horasGuardia(0),
      tarifaHoraExtra(0.0),
      tarifaHoraGuardia(0.0) {}

// Getters y setters
std::string Medico::getEspecialidad() const {
    return especialidad;
}

void Medico::setEspecialidad(const std::string& especialidad) {
    this->especialidad = especialidad;
}

void Medico::registrarHorasExtras(int horas) {
    if (horas > 0) {
        horasExtras += horas;
    }
}

void Medico::registrarHorasGuardia(int horas) {
    if (horas > 0) {
        horasGuardia += horas;
    }
}

// Cálculos de pagos adicionales
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

// Configuración de tarifas
void Medico::setTarifaHoraExtra(double tarifa) {
    if (tarifa >= 0) {
        tarifaHoraExtra = tarifa;
    }
}

void Medico::setTarifaHoraGuardia(double tarifa) {
    if (tarifa >= 0) {
        tarifaHoraGuardia = tarifa;
    }
}
