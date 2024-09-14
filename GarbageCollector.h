#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H

#include <unordered_map>
#include <thread>
#include <atomic>
#include <chrono>
#include "MPointer.h"

class MPointerGC {
public:
    static MPointerGC& Instance();

    // Registrar un nuevo MPointer en el sistema y devolver el ID
    template <typename T>
    int RegisterPointer(MPointer<T> ptr);

    // Incrementar el contador de referencias
    void IncrementReference(int id);

    // Disminuir el contador de referencias
    void DecrementReference(int id);

    void StartGarbageCollector();
    void StopGarbageCollector();

    void GarbageCollectorTask();  // Ciclo de limpieza

private:
    MPointerGC();
    ~MPointerGC();

    std::unordered_map<int, std::pair<MPointer<void>, int>> pointer_map; // Mapa de punteros y referencias
    int next_id;  // ID autogenerado
    std::atomic<bool> running;  // Control del hilo del GC
    std::thread gc_thread;      // Hilo del Garbage Collector
};

#endif
