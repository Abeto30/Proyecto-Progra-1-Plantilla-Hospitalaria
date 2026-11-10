#include "Enfermero.h"
#include <cmath>

// Validar textos
bool turnoValido(const std::string& texto) {
    return !texto.empty() &&
           texto.find_first_not_of(" \t\n\r") != std::string::npos;
}

// Constructor
Enfermero::Enfermero(int id,
                     const std::string& nombre,
                     const std::string& identificacion,
                     const std::string& telefono,
                     const std::string& correo,
                     double salarioBase,
                     const std::string& turno)
    : Empleado(id, nombre, identificacion, telefono, correo, salarioBase),
      turno(turnoValido(turno) ? turno : ""),
      horasExtras(0),
      horasNocturnas(0),
      tarifaHoraExtra(0.0),
      tarifaHoraNocturna(0.0) {
}

// Getter
std::string Enfermero::getTurno() const {
    return turno;
}

// Setter
void Enfermero::setTurno(const std::string& turno) {
    if (turnoValido(turno)) {
        this->turno = turno;
    }
}

int Enfermero::getHorasExtras() const {
    return horasExtras;
}

int Enfermero::getHorasNocturnas() const {
    return horasNocturnas;
}

double Enfermero::getTarifaHoraExtra() const {
    return tarifaHoraExtra;
}

double Enfermero::getTarifaHoraNocturna() const {
    return tarifaHoraNocturna;
}

// Registrar horas extras
void Enfermero::registrarHorasExtras(int horas) {
    if (horas > 0 && horas <= 1000000 - horasExtras) {
        horasExtras += horas;
    }
}

// Registrar horas nocturnas
void Enfermero::registrarHorasNocturnas(int horas) {
    if (horas > 0 && horas <= 1000000 - horasNocturnas) {
        horasNocturnas += horas;
    }
}

// Calcular pagos adicionales
double Enfermero::calcularPagoHorasExtras() const {
    return horasExtras * tarifaHoraExtra;
}

double Enfermero::calcularPagoHorasNocturnas() const {
    return horasNocturnas * tarifaHoraNocturna;
}

// Configurar tarifas
void Enfermero::setTarifaHoraExtra(double tarifa) {
    if (std::isfinite(tarifa) && tarifa >= 0) {
        tarifaHoraExtra = tarifa;
    }
}

void Enfermero::setTarifaHoraNocturna(double tarifa) {
    if (std::isfinite(tarifa) && tarifa >= 0) {
        tarifaHoraNocturna = tarifa;
    }
}

// Métodos polimórficos
std::string Enfermero::getTipoEmpleado() const {
    return "Enfermero";
}

double Enfermero::calcularSalarioBruto() const {
    return getSalarioBase()
           + calcularPagoHorasExtras()
           + calcularPagoHorasNocturnas();
}