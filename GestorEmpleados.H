#ifndef GESTOR_EMPLEADOS_H
#define GESTOR_EMPLEADOS_H

#include "Empleado.h"
#include "Lista.h"

class GestorEmpleados {
private:
    Lista<Empleado*> empleados;

public:
    GestorEmpleados();
    ~GestorEmpleados();

    bool agregarEmpleado(Empleado* empleado);
    Empleado* buscarEmpleadoPorId(int id) const;
    bool eliminarEmpleadoPorId(int id);

    int getCantidadEmpleados() const;
    bool estaEmpleadoActivo(int id) const;

    void limpiarEmpleados();
   
};

#endif // GESTOREMPLEADOS.h