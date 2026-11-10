#ifndef PUESTO_H
#define PUESTO_H

#include <string>

class Puesto {
private:
    int id;
    std::string nombre;
    std::string descripcion;

public:
    Puesto(int id,
           const std::string& nombre,
           const std::string& descripcion);

    int getId() const;
    std::string getNombre() const;
    std::string getDescripcion() const;

    void setNombre(const std::string& nombre);
    void setDescripcion(const std::string& descripcion);
};

#endif // PUESTO.h