#include "ComprobantePago.h"
#include <stdexcept>
#include <cmath>

// Constructor
ComprobantePago::ComprobantePago(int id,
                                 Empleado* empleado,
                                 Departamento* departamento,
                                 double salarioBruto,
                                 double deducciones,
                                 const std::string& fecha)
    : id(id),
      empleado(empleado),
      departamento(departamento),
      salarioBruto(salarioBruto),
      deducciones(deducciones),
      salarioNeto(0),
      fecha(fecha) {

    if (id <= 0) {
        throw std::invalid_argument("El ID debe ser mayor que cero.");
    }

    if (empleado == nullptr || departamento == nullptr) {
        throw std::invalid_argument("Empleado o departamento invalido.");
    }

    if (!std::isfinite(salarioBruto) || salarioBruto < 0) {
        throw std::invalid_argument("El salario bruto es invalido.");
    }

    if (!std::isfinite(deducciones) ||
        deducciones < 0 ||
        deducciones > salarioBruto) {
        throw std::invalid_argument("Las deducciones son invalidas.");
    }

    if (fecha.empty() ||
        fecha.find_first_not_of(" \t\n\r") == std::string::npos) {
        throw std::invalid_argument("La fecha no puede estar vacia.");
    }

    calcularSalarioNeto();
}

// Obtener ID
int ComprobantePago::getId() const {
    return id;
}

// Obtener empleado
Empleado* ComprobantePago::getEmpleado() const {
    return empleado;
}

// Obtener departamento
Departamento* ComprobantePago::getDepartamento() const {
    return departamento;
}

// Obtener salario bruto
double ComprobantePago::getSalarioBruto() const {
    return salarioBruto;
}

// Obtener deducciones
double ComprobantePago::getDeducciones() const {
    return deducciones;
}

// Obtener salario neto
double ComprobantePago::getSalarioNeto() const {
    return salarioNeto;
}

// Obtener fecha
const std::string& ComprobantePago::getFecha() const {
    return fecha;
}

// Modificar deducciones
void ComprobantePago::setDeducciones(double deducciones) {
    if (!std::isfinite(deducciones) ||
        deducciones < 0 ||
        deducciones > salarioBruto) {
        throw std::invalid_argument("Las deducciones son invalidas.");
    }

    this->deducciones = deducciones;
    calcularSalarioNeto();
}

// Calcular salario neto
void ComprobantePago::calcularSalarioNeto() {
    salarioNeto = salarioBruto - deducciones;
}