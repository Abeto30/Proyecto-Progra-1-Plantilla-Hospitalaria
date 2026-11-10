
#ifndef COMPROBANTE_PAGO_H
#define COMPROBANTE_PAGO_H

#include <string>

class ComprobantePago {
private:
    int id;

    int empleadoId;
    std::string nombreEmpleado;
    std::string identificacion;
    std::string tipoEmpleado;

    int departamentoId;
    std::string nombreDepartamento;

    double salarioBruto;
    double deducciones;
    double salarioNeto;

    std::string fecha;

public:
    ComprobantePago(
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
    );

    int getId() const;

    int getEmpleadoId() const;
    std::string getNombreEmpleado() const;
    std::string getIdentificacion() const;
    std::string getTipoEmpleado() const;

    int getDepartamentoId() const;
    std::string getNombreDepartamento() const;

    double getSalarioBruto() const;
    double getDeducciones() const;
    double getSalarioNeto() const;

    const std::string& getFecha() const;

    void setDeducciones(double deducciones);
    void calcularSalarioNeto();
};

#endif
// COMPROBANTEPago.h