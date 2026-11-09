#ifndef LISTA_H
#define LISTA_H

#include "Nodo.h"

template <typename T>
class Lista {

private:
    Nodo<T>* cabeza;
    int cantidad;

public:
    Lista();
    Lista(const Lista<T>& otra);
    Lista<T>& operator=(const Lista<T>& otra);
    ~Lista();

    bool estaVacia() const;
    int getCantidad() const;

    void insertarInicio(const T& dato);
    void insertarFinal(const T& dato);

    bool eliminar(int posicion);
    T obtener(int posicion) const;

    void limpiar();
};

#include "Lista.tpp"

#endif // LISTA.h