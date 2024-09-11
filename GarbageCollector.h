#ifndef GARBAGECOLLECTOR_H
#define GARBAGECOLLECTOR_H

#include <unordered_map>
#include <thread>
#include <atomic>
#include <chrono>

class MPointerGC {
public:

    static MPointerGC& Instance();

    // Registrar un nuevo puntero en el sistema y devolver el ID
    int RegisterPointer(void* ptr);

    // Incrementar el contador de referencias
    void IncrementReference(int id);

    // Disminuir el contador de referencias
    void DecrementReference(int id);


    void StartGarbageCollector();
    void StopGarbageCollector();

private:
    MPointerGC();  // Constructor
    ~MPointerGC(); // Destructor

    // Función  que ejecuta el ciclo de limpieza
    void GarbageCollectorTask();

    // Mapa que asocia IDs únicos con punteros y sus contadores de referencia
    std::unordered_map<int, std::pair<void*, int>> pointer_map;

    int next_id;  // ID

    std::atomic<bool> running;  //  detener el hilo
    std::thread gc_thread;      // Hilo del Garbage Collector
};

#endif // GARBAGECOLLECTOR_H
