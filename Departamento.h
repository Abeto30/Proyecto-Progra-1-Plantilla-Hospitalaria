#ifndef DEPARTAMENTO_H
#define DEPARTAMENTO_H

#include <string>
#include "Puesto.h"
#include "Lista.h"

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

    void agregarPuesto(const Puesto& puesto);
    int getCantidadPuestos() const;
};

#endif // DEPARTAMENTO.h