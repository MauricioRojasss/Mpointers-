#ifndef MPOINTER_H
#define MPOINTER_H

#include "GarbageCollector.h"

template <typename T>
class MPointer {
public:
    static MPointer<T> New();

    MPointer();

    // Constructor de copia con deep copy
    MPointer(const MPointer<T>& other);

    // Sobrecarga del operador de asignación con deep copy
    MPointer<T>& operator=(const MPointer<T>& other);

    ~MPointer();

    // Sobrecarga  para acceder al valor
    T& operator*();

    // Sobrecarga  para obtener la referencia
    T* operator&();

    // Sobrecarga  para acceder a los miembros del puntero
    T* operator->();

    // Método para verificar si el MPointer está "nulo"
    bool isNull() const;

private:
    T* ptr;  // Puntero interno encapsulado
    int id;  // Identificador único para el puntero
};

#include "MPointer.cpp"
#endif
