
#include "Almacenamiento.h"

#include <fstream>
#include <string>
#include <iterator>
#include <filesystem>
#include <system_error>

namespace {

const std::string ARCHIVO_EMPLEADOS =
    "Datos/Archivos/empleados.txt";

const std::string ARCHIVO_DEPARTAMENTOS =
    "Datos/Archivos/departamentos.txt";

const std::string ARCHIVO_PLANILLA =
    "Datos/Archivos/planilla.txt";

// Guarda información en un archivo de texto.
bool guardarArchivo(const std::string& ruta,
                    const std::string& datos) {

    // Crear la carpeta si todavía no existe.
    std::error_code error;

    std::filesystem::create_directories(
        "Datos/Archivos", error
    );

    if (error) {
        return false;
    }

    std::ofstream archivo(ruta, std::ios::out | std::ios::trunc);

    if (!archivo.is_open()) {
        return false;
    }

    archivo << datos;

    // Verificar que la escritura haya funcionado.
    if (!archivo.good()) {
        return false;
    }

    archivo.close();

    // Verificar que el cierre no haya producido errores.
    return !archivo.fail();
}

// Carga información desde un archivo de texto.
bool cargarArchivo(const std::string& ruta,
                   std::string& datos) {

    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        datos.clear();
        return false;
    }

    datos.assign(
        std::istreambuf_iterator<char>(archivo),
        std::istreambuf_iterator<char>()
    );

    // Detectar errores durante la lectura.
    if (archivo.bad()) {
        datos.clear();
        return false;
    }

    archivo.close();

    return true;
}

}

// Métodos para empleados.
bool AlmacenamientoArchivos::guardarEmpleados(
    const std::string& datos) {

    return guardarArchivo(ARCHIVO_EMPLEADOS, datos);
}

bool AlmacenamientoArchivos::cargarEmpleados(
    std::string& datos) {

    return cargarArchivo(ARCHIVO_EMPLEADOS, datos);
}

// Métodos para departamentos.
bool AlmacenamientoArchivos::guardarDepartamentos(
    const std::string& datos) {

    return guardarArchivo(ARCHIVO_DEPARTAMENTOS, datos);
}

bool AlmacenamientoArchivos::cargarDepartamentos(
    std::string& datos) {

    return cargarArchivo(ARCHIVO_DEPARTAMENTOS, datos);
}

// Métodos para planilla.
bool AlmacenamientoArchivos::guardarPlanilla(
    const std::string& datos) {

    return guardarArchivo(ARCHIVO_PLANILLA, datos);
}

bool AlmacenamientoArchivos::cargarPlanilla(
    std::string& datos) {

    return cargarArchivo(ARCHIVO_PLANILLA, datos);
}
