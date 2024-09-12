#include "MPointer.h"


template <typename T>
MPointer<T>::MPointer() : ptr(nullptr), id(-1) {}

// Constructor de copia  (deep copy)
template <typename T>
MPointer<T>::MPointer(const MPointer<T>& other) {
    if (other.ptr != nullptr) {
        // Crear una copia profunda del valor apuntado
        ptr = new T(*other.ptr);
    } else {
        ptr = nullptr;
    }
    id = MPointerGC::Instance().RegisterPointer(ptr);  // Registrar el nuevo puntero en el GC
}

// Sobrecarga del operador de asignación con deep copy
template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {  // Evitar autoasignación
        // Liberar la memoria del puntero actual si existe
        if (ptr != nullptr) {
            delete ptr;
        }

        // Realizar deep copy del otro puntero
        if (other.ptr != nullptr) {
            ptr = new T(*other.ptr);
        } else {
            ptr = nullptr;
        }

        MPointerGC::Instance().DecrementReference(id);  // Disminuir la referencia del puntero antiguo

        id = MPointerGC::Instance().RegisterPointer(ptr);  // Registrar el nuevo puntero en el GC
    }
    return *this;
}

// Destructor
template <typename T>
MPointer<T>::~MPointer() {
    MPointerGC::Instance().DecrementReference(id);  // Disminuir la referencia
    if (ptr != nullptr) {
        delete ptr;  // Liberar la memoria
    }
}

// Sobrecarga del operador *
template <typename T>
T& MPointer<T>::operator*() {
    return *ptr;
}

// Sobrecarga del operador * para valores constantes
template <typename T>
const T& MPointer<T>::operator*() const {
    return *ptr;
}

// Sobrecarga del operador &
template <typename T>
T* MPointer<T>::operator&() {
    return ptr;
}

// Crear un nuevo MPointer con memoria asignada
template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T> mp;
    mp.ptr = new T();  // Reservar memoria para un objeto de tipo T
    mp.id = MPointerGC::Instance().RegisterPointer(mp.ptr);  // Registrar el puntero en el GarbageCollector
    return mp;
}
