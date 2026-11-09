#ifndef GESTOR_EMPLEADOS_H
#define GESTOR_EMPLEADOS_H

#include "../Clases/Empleado.h"
#include "../Listas/Lista.h"

class GestorEmpleados {
private:
    Lista<Empleado*> empleados;

public:
    GestorEmpleados();
    ~GestorEmpleados();

    GestorEmpleados(const GestorEmpleados&) = delete;
    GestorEmpleados& operator=(const GestorEmpleados&) = delete;

    bool agregarEmpleado(Empleado* empleado);
    Empleado* buscarEmpleadoPorId(int id) const;
    bool eliminarEmpleadoPorId(int id);

    int getCantidadEmpleados() const;
    bool estaEmpleadoActivo(int id) const;

    void limpiarEmpleados();
    Empleado* obtenerEmpleadoEnPosicion(int posicion) const;
};

#endif