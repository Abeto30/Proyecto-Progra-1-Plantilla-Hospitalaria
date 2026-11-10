#ifndef ALMACENAMIENTO_H
#define ALMACENAMIENTO_H

#include <string>

class Almacenamiento {
public:
    virtual ~Almacenamiento() = default;

    virtual bool guardarEmpleados(const std::string& datos) = 0;
    virtual bool cargarEmpleados(std::string& datos) = 0;

    virtual bool guardarDepartamentos(const std::string& datos) = 0;
    virtual bool cargarDepartamentos(std::string& datos) = 0;

    virtual bool guardarPlanilla(const std::string& datos) = 0;
    virtual bool cargarPlanilla(std::string& datos) = 0;
};

class AlmacenamientoArchivos : public Almacenamiento {
public:
    bool guardarEmpleados(const std::string& datos) override;
    bool cargarEmpleados(std::string& datos) override;

    bool guardarDepartamentos(const std::string& datos) override;
    bool cargarDepartamentos(std::string& datos) override;

    bool guardarPlanilla(const std::string& datos) override;
    bool cargarPlanilla(std::string& datos) override;
};

#endif
//Almacenamiento .h 