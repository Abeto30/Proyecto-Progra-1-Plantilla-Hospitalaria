#ifndef Empleado_h
#define Empleado_h 
#include <string>

class Empleado {
    private:
        int id;
        std::string nombre;
        std::string identificacion;
        std::string telefono;
        std::string correo;
        double salarioBase;
        bool activo;

    public:
      Empleado(int id, 
        const std::string& nombre, 
        const std::string& identificacion, 
        const std::string& telefono, 
        const std::string& correo, 
        double salarioBase); 

virtual ~Empleado();

        int getId() const;
        std::string getNombre() const;
        std::string getIdentificacion() const;
        std::string getTelefono() const;
        std::string getCorreo() const;
        double getSalarioBase() const;
        bool estaActivo() const;

        void setNombre(const std::string& nombre);
        void setIdentificacion(const std::string& identificacion);
        void setTelefono(const std::string& telefono);
        void setCorreo(const std::string& correo);
        void setSalarioBase(double salarioBase);
        void setActivo(bool activo);

        virtual std::string getTipoEmpleado() const = 0;
        virtual double calcularSalarioBruto() const = 0;
};

#endif // Empleado.h 