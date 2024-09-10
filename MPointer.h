#ifndef MPOINTER_H
#define MPOINTER_H

#include "GarbageCollector.h"  // Incluir la gestión de memoria

 template <typename T>
class MPointer {
public:
    // Crear un nuevo MPointer con memoria asignada para el tipo T
    static MPointer<T> New();

    // Constructor por defecto
    MPointer();

    // Constructor de copia
    MPointer(const MPointer<T>& other);

    // Sobrecarga del operador de asignación
    MPointer<T>& operator=(const MPointer<T>& other);

    // Destructor
    ~MPointer();

    // Sobrecarga del operador * para acceder al valor
    T& operator*();

    // Sobrecarga del operador & para obtener la referencia
    T* operator&();

private:
    T* ptr;  // Puntero interno encapsulado
    int id;  // Identificador único para el puntero en MPointerGC
};

#include "MPointer.cpp"  // Incluir la implementación de la clase template
#endif
