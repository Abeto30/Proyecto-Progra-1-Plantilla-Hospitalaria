#ifndef ENFERMERO_H
#define ENFERMERO_H

#include "Empleado.h"
#include <string>

class Enfermero : public Empleado {
private:
    std::string turno;
    int horasExtras;
    int horasNocturnas;
    double tarifaHoraExtra;
    double tarifaHoraNocturna;

public:
    Enfermero(int id,
              const std::string& nombre,
              const std::string& identificacion,
              const std::string& telefono,
              const std::string& correo,
              double salarioBase,
              const std::string& turno);

    std::string getTurno() const;
    void setTurno(const std::string& turno);

    void registrarHorasExtras(int horas);
    void registrarHorasNocturnas(int horas);

    double calcularPagoHorasExtras() const;
    double calcularPagoHorasNocturnas() const;

    void setTarifaHoraExtra(double tarifa);
    void setTarifaHoraNocturna(double tarifa);

    std::string getTipoEmpleado() const override;
    double calcularSalarioBruto() const override;
};

#endif // ENFERMERO.H