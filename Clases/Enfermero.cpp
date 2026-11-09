#include "Enfermero.h"

Enfermero::Enfermero(int id, 
                     const std::string& nombre, 
                     const std::string& identificacion, 
                     const std::string& telefono, 
                     const std::string& correo, 
                     double salarioBase,
                     const std::string& turno)
    : Empleado(id, nombre, identificacion, telefono, correo, salarioBase),
      turno(turno),
      horasExtras(0),
      horasNocturnas(0),
      tarifaHoraExtra(0.0),
      tarifaHoraNocturna(0.0) {
}

std::string Enfermero::getTurno() const {
    return turno;
}

void Enfermero::setTurno(const std::string& turno) {
    this->turno = turno;
}

void Enfermero::registrarHorasExtras(int horas) {
    if (horas > 0) {
        horasExtras += horas;
    }
}

void Enfermero::registrarHorasNocturnas(int horas) {
    if (horas > 0) {
        horasNocturnas += horas;
    }
}

double Enfermero::calcularPagoHorasExtras() const {
    return horasExtras * tarifaHoraExtra;
}

double Enfermero::calcularPagoHorasNocturnas() const {
    return horasNocturnas * tarifaHoraNocturna;
}

void Enfermero::setTarifaHoraExtra(double tarifa) {
    if (tarifa >= 0) {
        tarifaHoraExtra = tarifa;
    }
}

void Enfermero::setTarifaHoraNocturna(double tarifa) {
    if (tarifa >= 0) {
        tarifaHoraNocturna = tarifa;
    }
}

std::string Enfermero::getTipoEmpleado() const {
    return "Enfermero";
}

double Enfermero::calcularSalarioBruto() const {
    return getSalarioBase() + calcularPagoHorasExtras() + calcularPagoHorasNocturnas();
}
//Enfermero.cpp