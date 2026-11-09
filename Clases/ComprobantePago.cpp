#include "ComprobantePago.h"
#include <stdexcept>

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
    if (deducciones < 0) {
        throw std::invalid_argument("Las deducciones no pueden ser negativas.");
    }

    this->deducciones = deducciones;
    calcularSalarioNeto();
}

// Calcular salario neto
void ComprobantePago::calcularSalarioNeto() {
    salarioNeto = salarioBruto - deducciones;
}
//ComprobantePago.cpp