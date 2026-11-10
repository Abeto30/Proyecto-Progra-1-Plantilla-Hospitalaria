#ifndef ENTRADA_H
#define ENTRADA_H

#include <string>

using namespace std;

void limpiarEntradaInvalida();

string leerToken(const string& mensaje);

string leerLinea(const string& mensaje);

int leerEntero(const string& mensaje, int minimo, int maximo);

double leerDouble(const string& mensaje, double minimo, bool estrictoMayor);

bool leerBooleano(const string& mensaje);

#endif
//Entrada .h