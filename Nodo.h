#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {

private:
    T dato;
    Nodo<T>* siguiente;


public:
    Nodo(const T& dato);

    T getDato() const;
    void setDato(const T& dato);

    Nodo<T>* getSiguiente() const;
    void setSiguiente(Nodo<T>* siguiente);

};

#include "Nodo.tpp"

#endif // NODO.h