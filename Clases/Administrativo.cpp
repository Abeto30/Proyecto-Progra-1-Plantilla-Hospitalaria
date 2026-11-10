#include "Administrativo.h"
#include <cmath>

// Validar textos
bool cargoValido(const std::string& texto) {
    return !texto.empty() &&
           texto.find_first_not_of(" \t\n\r") != std::string::npos;
}

// Constructor
Administrativo::Administrativo(int id,
                               const std::string& nombre,
                               const std::string& identificacion,
                               const std::string& telefono,
                               const std::string& correo,
                               double salarioBase,
                               const std::string& cargo)
    : Empleado(id, nombre, identificacion, telefono, correo, salarioBase),
      cargo(cargoValido(cargo) ? cargo : ""),
      horasExtras(0),
      tarifaHoraExtra(0.0) {
}

// Getter
std::string Administrativo::getCargo() const {
    return cargo;
}

// Setter
void Administrativo::setCargo(const std::string& cargo) {
    if (cargoValido(cargo)) {
        this->cargo = cargo;
    }
}

int Administrativo::getHorasExtras() const {
    return horasExtras;
}

double Administrativo::getTarifaHoraExtra() const {
    return tarifaHoraExtra;
}

// Registrar horas extras
void Administrativo::registrarHorasExtras(int horas) {
    if (horas > 0 && horas <= 1000000 - horasExtras) {
        horasExtras += horas;
    }
}

// Calcular pago de horas extras
double Administrativo::calcularPagoHorasExtras() const {
    return horasExtras * tarifaHoraExtra;
}

// Configurar tarifa
void Administrativo::setTarifaHoraExtra(double tarifa) {
    if (std::isfinite(tarifa) && tarifa >= 0) {
        tarifaHoraExtra = tarifa;
    }
}

// Métodos polimórficos
std::string Administrativo::getTipoEmpleado() const {
    return "Administrativo";
}

double Administrativo::calcularSalarioBruto() const {
    return getSalarioBase() + calcularPagoHorasExtras();
}