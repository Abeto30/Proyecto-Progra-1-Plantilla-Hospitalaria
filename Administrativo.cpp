#include "Administrativo.h"

Administrativo::Administrativo(int id,
                               const std::string& nombre,
                               const std::string& identificacion,
                               const std::string& telefono,
                               const std::string& correo,
                               double salarioBase,
                               const std::string& cargo)
    : Empleado(id, nombre, identificacion, telefono, correo, salarioBase),
      cargo(cargo),
      horasExtras(0),
      tarifaHoraExtra(0.0) {
}

std::string Administrativo::getCargo() const {
    return cargo;
}

void Administrativo::setCargo(const std::string& cargo) {
    this->cargo = cargo;
} 
void Administrativo::registrarHorasExtras(int horas) {
    if (horas >= 0) {
        horasExtras += horas;
    }
}

double Administrativo::calcularPagoHorasExtras() const {
    return horasExtras * tarifaHoraExtra;
}

void Administrativo::setTarifaHoraExtra(double tarifa) {
    if (tarifa >= 0) {
        tarifaHoraExtra = tarifa;
    }
}

std::string Administrativo::getTipoEmpleado() const {
    return "Administrativo";
}

double Administrativo::calcularSalarioBruto() const {
    return getSalarioBase() + calcularPagoHorasExtras();
}
