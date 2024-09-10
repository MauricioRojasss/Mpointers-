#include "MPointer.h"

template <typename T>
MPointer<T>::MPointer() : ptr(nullptr) {}

template <typename T>
MPointer<T>::MPointer(const MPointer<T>& other) {
    // Implementar copia profunda
}

template <typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    // Implementar asignación profunda
    return *this;
}

template <typename T>
MPointer<T>::~MPointer() {
    // Liberar memoria
}

template <typename T>
T& MPointer<T>::operator*() {
    return *ptr;
}

template <typename T>
const T& MPointer<T>::operator*() const {
    return *ptr;
}

template <typename T>
T* MPointer<T>::operator&() {
    return ptr;
}

template <typename T>
MPointer<T> MPointer<T>::New() {
    // Implementar creación de nueva instancia
    return MPointer<T>();
}
