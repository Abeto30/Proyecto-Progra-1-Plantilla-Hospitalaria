template <typename T>
Nodo<T>::Nodo(const T& dato)
    : dato(dato), siguiente(nullptr) {
}

template <typename T>
T Nodo<T>::getDato() const {
    return dato;
}

template <typename T>
void Nodo<T>::setDato(const T& dato) {
    this->dato = dato;
}

template <typename T>
Nodo<T>* Nodo<T>::getSiguiente() const {
    return siguiente;
}

template <typename T>
void Nodo<T>::setSiguiente(Nodo<T>* siguiente) {
    this->siguiente = siguiente;
}
//Nodo.tpp