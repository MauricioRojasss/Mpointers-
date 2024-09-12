#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include "Nodo.h"
#include "MPointer.h"

class ListaEnlazada {
public:
    ListaEnlazada();
    ~ListaEnlazada();

    void agregar(int valor);
    void imprimirLista() const;
    int get(int index) const;             // Obtener el valor en un índice
    void set(int index, int valor);       // Establecer un valor en un índice
    int size() const;                     // Obtener el tamaño de la lista
    void intercambiar(int i, int j)

private:
    MPointer<Nodo> primero = nullptr;
    int longitud;  // Llevar cuenta del tamaño de la lista
};



#endif
