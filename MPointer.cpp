#include "MPointer.h"

// Constructor por defecto
template <typename T>
MPointer<T>::MPointer() : ptr(nullptr), id(-1) {}

// Constructor de copia
template <typename T>
MPointer<T>::MPointer(const MPointer<T>& other) {
    ptr = other.ptr;  // Copiar el puntero
    id = other.id;    // Copiar el ID
    MPointerGC::Instance().IncrementReference(id);  // Incrementar la referencia en el GC
}

// Sobrecarga del operador de asignación
template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {  // Evitar autoasignación
        MPointerGC::Instance().DecrementReference(id);  // Disminuir la referencia actual
        ptr = other.ptr;  // Asignar el puntero del otro MPointer
        id = other.id;    // Copiar el ID
        MPointerGC::Instance().IncrementReference(id);  // Incrementar la referencia en el GC
    }
    return *this;
}

// Destructor
template <typename T>
MPointer<T>::~MPointer() {
    MPointerGC::Instance().DecrementReference(id);  // Disminuir la referencia
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
