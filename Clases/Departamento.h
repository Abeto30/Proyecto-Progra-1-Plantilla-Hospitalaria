#ifndef DEPARTAMENTO_H
#define DEPARTAMENTO_H

#include <string>
#include "Puesto.h"
#include "../Listas/Lista.h"

class Departamento {
private:
    int id;
    std::string nombre;
    std::string descripcion;
    Lista<Puesto> puestos;

public:
    Departamento(int id,
                 const std::string& nombre,
                 const std::string& descripcion);

    int getId() const;
    std::string getNombre() const;
    std::string getDescripcion() const;

    void setNombre(const std::string& nombre);
    void setDescripcion(const std::string& descripcion);

    bool agregarPuesto(const Puesto& puesto);
    bool existePuestoID(int id) const;
    bool eliminarPuestoID(int id);

    Puesto obtenerPuestoEnPosicion(int posicion) const;

    int getCantidadPuestos() const;
};

#endif // DEPARTAMENTO.h