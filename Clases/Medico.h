#ifndef MEDICO_H
#define MEDICO_H

#include "Empleado.h"
#include <string>

class Medico : public Empleado {
private:
    std::string especialidad;
    int horasExtras;
    int horasGuardia;
    double tarifaHoraExtra;
    double tarifaHoraGuardia;

public:
    Medico(int id,
           const std::string& nombre,
           const std::string& identificacion,
           const std::string& telefono,
           const std::string& correo,
           double salarioBase,
           const std::string& especialidad);

    std::string getEspecialidad() const;
    void setEspecialidad(const std::string& especialidad);
    int getHorasExtras() const;
    int getHorasGuardia() const;

    double getTarifaHoraExtra() const;
    double getTarifaHoraGuardia() const;

    void registrarHorasExtras(int horas);
    void registrarHorasGuardia(int horas);

    double calcularpagoHorasExtras() const;
    double calcularpagoHorasGuardia() const;

    std::string getTipoEmpleado() const override;
    double calcularSalarioBruto() const override;

    void setTarifaHoraExtra(double tarifa);
    void setTarifaHoraGuardia(double tarifa);
};

#endif // MEDICO.h