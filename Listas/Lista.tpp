#include <stdexcept>

// Constructor
template <typename T>
Lista<T>::Lista()
    : cabeza(nullptr), cantidad(0) {
}

// Constructor de copia
template <typename T>
Lista<T>::Lista(const Lista<T>& otra)
    : cabeza(nullptr), cantidad(0) {

    Nodo<T>* actual = otra.cabeza;

    while (actual != nullptr) {
        insertarFinal(actual->getDato());
        actual = actual->getSiguiente();
    }
}

// Operador de asignación
template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& otra) {
    if (this != &otra) {
        limpiar();

        Nodo<T>* actual = otra.cabeza;

        while (actual != nullptr) {
            insertarFinal(actual->getDato());
            actual = actual->getSiguiente();
        }
    }

    return *this;
}

// Destructor
template <typename T>
Lista<T>::~Lista() {
    limpiar();
}

// Comprueba si está vacía
template <typename T>
bool Lista<T>::estaVacia() const {
    return cabeza == nullptr;
}

// Devuelve la cantidad de elementos
template <typename T>
int Lista<T>::getCantidad() const {
    return cantidad;
}

// Inserta al inicio
template <typename T>
void Lista<T>::insertarInicio(const T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);

    nuevo->setSiguiente(cabeza);
    cabeza = nuevo;

    cantidad++;
}

// Inserta al final
template <typename T>
void Lista<T>::insertarFinal(const T& dato) {
    Nodo<T>* nuevo = new Nodo<T>(dato);

    if (estaVacia()) {
        cabeza = nuevo;
    } else {
        Nodo<T>* actual = cabeza;

        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }

        actual->setSiguiente(nuevo);
    }

    cantidad++;
}

// Elimina por posición (comenzando desde 0)
template <typename T>
bool Lista<T>::eliminar(int posicion) {
    if (posicion < 0 || posicion >= cantidad) {
        return false;
    }

    Nodo<T>* eliminarNodo;

    if (posicion == 0) {
        eliminarNodo = cabeza;
        cabeza = cabeza->getSiguiente();
    } else {
        Nodo<T>* actual = cabeza;

        for (int i = 0; i < posicion - 1; i++) {
            actual = actual->getSiguiente();
        }

        eliminarNodo = actual->getSiguiente();
        actual->setSiguiente(eliminarNodo->getSiguiente());
    }

    delete eliminarNodo;
    cantidad--;

    return true;
}

// Obtiene un elemento por posición
template <typename T>
T Lista<T>::obtener(int posicion) const {
    if (posicion < 0 || posicion >= cantidad) {
        throw std::out_of_range("Posicion fuera de rango");
    }

    Nodo<T>* actual = cabeza;

    for (int i = 0; i < posicion; i++) {
        actual = actual->getSiguiente();
    }

    return actual->getDato();
}

// Libera todos los nodos
template <typename T>
void Lista<T>::limpiar() {
    while (cabeza != nullptr) {
        Nodo<T>* temporal = cabeza;
        cabeza = cabeza->getSiguiente();

        delete temporal;
    }

    cantidad = 0;
}//Lista.tpp