#include "ListaEnlazada.h"
#include "Ordenamientos.h"
#include <iostream>

int main() {
    ListaEnlazada lista;

    lista.agregar(3);
    lista.agregar(1);
    lista.agregar(4);
    lista.agregar(2);

    std::cout << "Lista original: ";
    lista.imprimirLista();

    std::cout << "Ordenando con BubbleSort..." << std::endl;
    bubbleSort(lista);

    std::cout << "Lista ordenada: ";
    lista.imprimirLista();

    return 0;
}
