#include "Almacenamiento.h"

#include <fstream>
#include <string>
#include <iterator>

const std::string ARCHIVO_EMPLEADOS = "Datos/Archivos/empleados.txt";
const std::string ARCHIVO_DEPARTAMENTOS = "Datos/Archivos/departamentos.txt";
const std::string ARCHIVO_PLANILLA = "Datos/Archivos/planilla.txt";

// Guarda información en un archivo de texto
bool guardarArchivo(const std::string& ruta, const std::string& datos) {
    std::ofstream archivo(ruta);

    if (!archivo.is_open()) {
        return false;
    }

    archivo << datos;

    if (!archivo.good()) {
        return false;
    }

    archivo.close();
    return true;
}

// Carga información desde un archivo de texto
bool cargarArchivo(const std::string& ruta, std::string& datos) {
    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        datos.clear();
        return false;
    }

    datos.assign(
        std::istreambuf_iterator<char>(archivo),
        std::istreambuf_iterator<char>()
    );

    archivo.close();
    return true;
}

bool AlmacenamientoArchivos::guardarEmpleados(const std::string& datos) {
    return guardarArchivo(ARCHIVO_EMPLEADOS, datos);
}

bool AlmacenamientoArchivos::cargarEmpleados(std::string& datos) {
    return cargarArchivo(ARCHIVO_EMPLEADOS, datos);
}

bool AlmacenamientoArchivos::guardarDepartamentos(const std::string& datos) {
    return guardarArchivo(ARCHIVO_DEPARTAMENTOS, datos);
}

bool AlmacenamientoArchivos::cargarDepartamentos(std::string& datos) {
    return cargarArchivo(ARCHIVO_DEPARTAMENTOS, datos);
}

bool AlmacenamientoArchivos::guardarPlanilla(const std::string& datos) {
    return guardarArchivo(ARCHIVO_PLANILLA, datos);
}

bool AlmacenamientoArchivos::cargarPlanilla(std::string& datos) {
    return cargarArchivo(ARCHIVO_PLANILLA, datos);
}