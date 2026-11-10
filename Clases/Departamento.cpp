
#include "ComprobantePago.h"

#include "Empleado.h"
#include "Departamento.h"

#include <stdexcept>
#include <cmath>

// Constructor para reconstruir comprobantes desde archivos
ComprobantePago::ComprobantePago(
    int id,
    int empleadoId,
    const std::string& nombreEmpleado,
    const std::string& identificacion,
    const std::string& tipoEmpleado,
    int departamentoId,
    const std::string& nombreDepartamento,
    double salarioBruto,
    double deducciones,
    const std::string& fecha
)
    : id(id),
      empleado(nullptr),
      departamento(nullptr),
      empleadoId(empleadoId),
      nombreEmpleado(nombreEmpleado),
      identificacion(identificacion),
      tipoEmpleado(tipoEmpleado),
      departamentoId(departamentoId),
      nombreDepartamento(nombreDepartamento),
      salarioBruto(salarioBruto),
      deducciones(deducciones),
      salarioNeto(0),
      fecha(fecha) {

    if (id <= 0 || empleadoId <= 0 || departamentoId <= 0) {
        throw std::invalid_argument("Los ID deben ser mayores que cero.");
    }

    if (nombreEmpleado.empty() ||
        identificacion.empty() ||
        tipoEmpleado.empty() ||
        nombreDepartamento.empty()) {
        throw std::invalid_argument(
            "Los datos del empleado o departamento son invalidos."
        );
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

// Constructor con referencias de agregacion
ComprobantePago::ComprobantePago(
    int id,
    Empleado* empleado,
    Departamento* departamento,
    double salarioBruto,
    double deducciones,
    const std::string& fecha
)
    : ComprobantePago(
        id,
        empleado != nullptr ? empleado->getId() : 0,
        empleado != nullptr ? empleado->getNombre() : "",
        empleado != nullptr ? empleado->getIdentificacion() : "",
        empleado != nullptr ? empleado->getTipoEmpleado() : "",
        departamento != nullptr ? departamento->getId() : 0,
        departamento != nullptr ? departamento->getNombre() : "",
        salarioBruto,
        deducciones,
        fecha
    ) {

    if (empleado == nullptr || departamento == nullptr) {
        throw std::invalid_argument(
            "El empleado y el departamento son obligatorios."
        );
    }

    this->empleado = empleado;
    this->departamento = departamento;
}

// Obtener ID del comprobante
int ComprobantePago::getId() const {
    return id;
}

// Obtener referencias de agregacion
Empleado* ComprobantePago::getEmpleado() const {
    return empleado;
}

Departamento* ComprobantePago::getDepartamento() const {
    return departamento;
}

// Obtener datos del empleado
int ComprobantePago::getEmpleadoId() const {
    return empleadoId;
}

std::string ComprobantePago::getNombreEmpleado() const {
    return nombreEmpleado;
}

std::string ComprobantePago::getIdentificacion() const {
    return identificacion;
}

std::string ComprobantePago::getTipoEmpleado() const {
    return tipoEmpleado;
}

// Obtener datos del departamento
int ComprobantePago::getDepartamentoId() const {
    return departamentoId;
}

std::string ComprobantePago::getNombreDepartamento() const {
    return nombreDepartamento;
}

// Obtener salarios
double ComprobantePago::getSalarioBruto() const {
    return salarioBruto;
}

double ComprobantePago::getDeducciones() const {
    return deducciones;
}

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
