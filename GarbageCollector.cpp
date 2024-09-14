#include "GarbageCollector.h"

MPointerGC::MPointerGC() : next_id(0), running(false) {}

MPointerGC::~MPointerGC() {
    StopGarbageCollector();
}

// Obtener la instancia del Garbage Collector
MPointerGC& MPointerGC::Instance() {
    static MPointerGC instance;
    return instance;
}

// Registrar un nuevo MPointer y devolver un ID único
template <typename T>
int MPointerGC::RegisterPointer(MPointer<T> ptr) {
    int id = next_id++;
    pointer_map[id] = {MPointer<void>(reinterpret_cast<void*>(ptr.operator&())), 1};  // Guardar el puntero con contador de referencia inicial 1
    return id;
}

// Incrementar la referencia del MPointer
void MPointerGC::IncrementReference(int id) {
    if (pointer_map.find(id) != pointer_map.end()) {
        pointer_map[id].second++;  // Incrementar el contador
    }
}

// Disminuir la referencia del MPointer y liberar memoria si llega a 0
void MPointerGC::DecrementReference(int id) {
    if (pointer_map.find(id) != pointer_map.end()) {
        pointer_map[id].second--;  // Disminuir el contador
        if (pointer_map[id].second == 0) {

            pointer_map.erase(id);  // Eliminar del mapa
        }
    }
}

// Iniciar el Garbage Collector
void MPointerGC::StartGarbageCollector() {
    running = true;
    gc_thread = std::thread(&MPointerGC::GarbageCollectorTask, this);  // Iniciar el hilo
}

// Detener el Garbage Collector
void MPointerGC::StopGarbageCollector() {
    running = false;  // Detener ciclo
    if (gc_thread.joinable()) {
        gc_thread.join();  // Esperar al hilo
    }
}

// Revisa periódicamente los punteros
void MPointerGC::GarbageCollectorTask() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        for (auto it = pointer_map.begin(); it != pointer_map.end();) {
            if (it->second.second == 0) {
                it = pointer_map.erase(it);  // Eliminar del mapa
            } else {
                ++it;
            }
        }
    }
}
