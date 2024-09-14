#include "ListaEnlazada.h"
#include <iostream>


ListaEnlazada::ListaEnlazada() : primero(), longitud(0) {}

// Destructor
ListaEnlazada::~ListaEnlazada() {}

// Agregar un nuevo valor al final de la lista
void ListaEnlazada::agregar(int valor) {
    MPointer<Nodo> nuevoNodo = MPointer<Nodo>::New();
    nuevoNodo->valor = valor;

    if (primero.isNull()) {
        primero = nuevoNodo;
    } else {
        MPointer<Nodo> actual = primero;
        while (!actual->siguiente.isNull()) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
    longitud++;
}

// Imprimir la lista
void ListaEnlazada::imprimirLista() const {
    if (primero.isNull()) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    MPointer<Nodo> actual = primero;
    while (!actual.isNull()) {
        std::cout << actual->valor << " -> ";
        actual = actual->siguiente;
    }
    std::cout << "nullptr" << std::endl;
}

// Obtener el valor en un índice específico
int ListaEnlazada::get(int index) const {
    if (index >= longitud) {
        throw std::out_of_range("Índice fuera de rango");
    }
    MPointer<Nodo> actual = primero;
    for (int i = 0; i < index; ++i) {
        actual = actual->siguiente;
    }
    return actual->valor;
}

// Establecer un valor en un índice específico
void ListaEnlazada::set(int index, int valor) {
    if (index >= longitud) {
        throw std::out_of_range("Índice fuera de rango");
    }
    MPointer<Nodo> actual = primero;
    for (int i = 0; i < index; ++i) {
        actual = actual->siguiente;
    }
    actual->valor = valor;
}

// Obtener el tamaño de la lista
int ListaEnlazada::size() const {
    return longitud;
}

// Intercambiar dos elementos de la lista
void ListaEnlazada::intercambiar(int i, int j) {
    if (i >= longitud || j >= longitud) {
        throw std::out_of_range("Índice fuera de rango");
    }
    int temp = get(i);
    set(i, get(j));
    set(j, temp);
}
