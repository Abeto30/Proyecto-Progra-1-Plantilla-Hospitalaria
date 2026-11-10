#ifndef SERIALIZADOR_DEPARTAMENTOS_H
#define SERIALIZADOR_DEPARTAMENTOS_H

#include <string>

class GestorDepartamentos;

class SerializadorDepartamentos {
public:
    static std::string serializar(const GestorDepartamentos& gestor);
};

#endif // SERIALIZADOR_DEPARTAMENTOS_H