#ifndef GESTOR_DEPARTAMENTOS_H
#define GESTOR_DEPARTAMENTOS_H

#include "Departamento.h"
#include "Lista.h"

class GestorDepartamentos {
private:
    Lista<Departamento*> departamentos;

public:
    GestorDepartamentos();
    ~GestorDepartamentos();

    bool agregarDepartamento(Departamento* departamento);
    Departamento* buscarDepartamentoPorId(int id) const;
    bool eliminarDepartamentoPorId(int id);

    int getCantidadDepartamentos() const;

    void limpiarDepartamentos();

    Departamento* obtenerDepartamentoEnPosicion(int posicion) const;
};

#endif