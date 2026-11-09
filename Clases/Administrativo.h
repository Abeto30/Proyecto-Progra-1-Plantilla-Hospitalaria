#ifndef Administrativo_H
#define Administrativo_H

#include "Empleado.h"
#include <string>

class Administrativo : public Empleado {
private:
    std::string cargo;
    int horasExtras;
    double tarifaHoraExtra;

public:
    Administrativo(int id,
                  const std::string& nombre,
                  const std::string& identificacion,
                  const std::string& telefono,
                  const std::string& correo,
                  double salarioBase,
                  const std::string& cargo);
        
    std::string getCargo() const;
    void setCargo(const std::string& cargo);

    void registrarHorasExtras(int horas);

    double calcularPagoHorasExtras() const;

    void setTarifaHoraExtra(double tarifa);

    std::string getTipoEmpleado() const override;
    double calcularSalarioBruto() const override;
};

#endif //Administrativo.H