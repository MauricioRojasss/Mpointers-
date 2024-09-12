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

    // Sobrecarga del operador * para acceder al valor
    T& operator*();

    // Sobrecarga del operador & para obtener la referencia
    T* operator&();

private:
    T* ptr;  // Puntero interno encapsulado
    int id;  // Identificador único para el puntero
};

#include "MPointer.cpp"
#endif
