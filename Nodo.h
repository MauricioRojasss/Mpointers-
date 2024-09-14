#ifndef NODO_H
#define NODO_H

#include "MPointer.h"

class Nodo {
public:
    int valor;
    MPointer<Nodo> siguiente;  // Inicializado por defecto

    Nodo();
    Nodo(int valor);  // Constructor con valor
};

#endif
