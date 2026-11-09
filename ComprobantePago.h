#ifndef COMPROBANTE_PAGO_H
#define COMPROBANTE_PAGO_H

#include <string>
#include "Empleado.h"
#include "Departamento.h"

class ComprobantePago {

private:
    int id;
    Empleado* empleado;
    Departamento* departamento;
    double salarioBruto;
    double deducciones;
    double salarioNeto;
    std::string fecha;

public:
    ComprobantePago(int id,
                    Empleado* empleado,
                    Departamento* departamento,
                    double salarioBruto,
                    double deducciones,
                    const std::string& fecha);

    int getId() const;
    Empleado* getEmpleado() const;
    Departamento* getDepartamento() const;
    double getSalarioBruto() const;
    double getDeducciones() const;
    double getSalarioNeto() const;
    const std::string& getFecha() const;

    void setDeducciones(double deducciones);
    void calcularSalarioNeto();
};

#endif // COMPROBANTEPago.h