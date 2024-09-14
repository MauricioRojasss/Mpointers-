#include "MPointer.h"

// Constructor por defecto que inicializa el puntero como "nulo"
template <typename T>
MPointer<T>::MPointer() : ptr(nullptr), id(-1) {}

// Constructor de copia (deep copy)
template <typename T>
MPointer<T>::MPointer(const MPointer<T>& other) {
    if (!other.isNull()) {
        // Crear una copia profunda usando MPointer
        ptr = new T(*other.ptr);
    } else {
        ptr = nullptr;
    }
    id = MPointerGC::Instance().RegisterPointer(*this);  // Registrar el nuevo MPointer
}

// Sobrecarga del operador de asignación con deep copy
template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {  // Evitar autoasignación
        // Liberar la memoria del puntero actual si existe
        if (!this->isNull()) {
            delete ptr;
        }

        // Realizar deep copy del otro puntero
        if (!other.isNull()) {
            ptr = new T(*other.ptr);
        } else {
            ptr = nullptr;
        }

        MPointerGC::Instance().DecrementReference(id);  // Disminuir la referencia del puntero antiguo

        id = MPointerGC::Instance().RegisterPointer(*this);  // Registrar el nuevo MPointer
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

// Sobrecarga del operador -> para acceder a los miembros del puntero
template <typename T>
T* MPointer<T>::operator->() {
    return ptr;
}

// Sobrecarga del operador & para obtener la referencia del puntero
template <typename T>
T* MPointer<T>::operator&() {
    return ptr;
}

// Verificar si el MPointer está en estado "nulo"
template <typename T>
bool MPointer<T>::isNull() const {
    return ptr == nullptr;
}

// Crear un nuevo MPointer con memoria asignada
template <typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T> mp;
    mp.ptr = new T();  // Reservar memoria para un objeto de tipo T
    mp.id = MPointerGC::Instance().RegisterPointer(mp);  // Registrar el puntero en el GarbageCollector
    return mp;
}
