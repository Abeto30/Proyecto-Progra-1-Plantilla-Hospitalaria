#ifndef GESTOR_DEPARTAMENTOS_H
#define GESTOR_DEPARTAMENTOS_H

#include "../Clases/Departamento.h"
#include "../Listas/Lista.h"

class GestorDepartamentos {
private:
    Lista<Departamento*> departamentos;

public:
    GestorDepartamentos();
    ~GestorDepartamentos();
    
    GestorDepartamentos(const GestorDepartamentos&) = delete;
    GestorDepartamentos& operator=(const GestorDepartamentos&) = delete;

    bool agregarDepartamento(Departamento* departamento);
    Departamento* buscarDepartamentoPorId(int id) const;
    bool eliminarDepartamentoPorId(int id);

    int getCantidadDepartamentos() const;

    void limpiarDepartamentos();

    Departamento* obtenerDepartamentoEnPosicion(int posicion) const;
};

#endif
//GestorDepartamentos.h