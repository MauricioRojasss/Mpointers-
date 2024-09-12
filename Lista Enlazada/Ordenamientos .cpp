#include "Ordenamientos.h"

// Función auxiliar para QuickSort
int particionar(ListaEnlazada& lista, int inicio, int fin) {
    int pivote = lista.get(fin);
    int i = inicio - 1;

    for (int j = inicio; j < fin; ++j) {
        if (lista.get(j) <= pivote) {
            i++;
            lista.intercambiar(i, j);
        }
    }
    lista.intercambiar(i + 1, fin);
    return i + 1;
}

// Implementación de QuickSort
void quickSort(ListaEnlazada& lista, int inicio, int fin) {
    if (inicio < fin) {
        int pi = particionar(lista, inicio, fin);
        quickSort(lista, inicio, pi - 1);
        quickSort(lista, pi + 1, fin);
    }
}

// Implementación de BubbleSort
void bubbleSort(ListaEnlazada& lista) {
    int n = lista.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (lista.get(j) > lista.get(j + 1)) {
                lista.intercambiar(j, j + 1);
            }
        }
    }
}

// Implementación de InsertionSort
void insertionSort(ListaEnlazada& lista) {
    int n = lista.size();
    for (int i = 1; i < n; ++i) {
        int key = lista.get(i);
        int j = i - 1;

        while (j >= 0 && lista.get(j) > key) {
            lista.set(j + 1, lista.get(j));
            j--;
        }
        lista.set(j + 1, key);
    }
}
