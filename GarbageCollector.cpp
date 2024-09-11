#include "MPointerGC.h"

// Constructor del Singleton
MPointerGC::MPointerGC() : next_id(0), running(false) {}

// Destructor
MPointerGC::~MPointerGC() {
    StopGarbageCollector();
}

// Obtener la instancia única
MPointerGC& MPointerGC::Instance() {
    static MPointerGC instance;
    return instance;
}

// Registrar un nuevo puntero y devolver un ID único
int MPointerGC::RegisterPointer(void* ptr) {
    int id = next_id++;
    pointer_map[id] = {ptr, 1};  // Guardar el puntero con un contador de referencia inicial de 1
    return id;
}

// Incrementar la referencia del puntero con el ID dado
void MPointerGC::IncrementReference(int id) {
    if (pointer_map.find(id) != pointer_map.end()) {
        pointer_map[id].second++;  // Incrementar el contador de referencias
    }
}

// Disminuir la referencia del puntero y liberar memoria si el contador llega a 0
void MPointerGC::DecrementReference(int id) {
    if (pointer_map.find(id) != pointer_map.end()) {
        pointer_map[id].second--;  // Disminuir el contador de referencias
        if (pointer_map[id].second == 0) {
            delete static_cast<char*>(pointer_map[id].first);  // Liberar la memoria del puntero
            pointer_map.erase(id);  // Eliminar la entrada del mapa
        }
    }
}


void MPointerGC::StartGarbageCollector() {
    running = true;
    gc_thread = std::thread(&MPointerGC::GarbageCollectorTask, this);  // Iniciar el hilo
}


void MPointerGC::StopGarbageCollector() {
    running = false;  // Detener el ciclo
    if (gc_thread.joinable()) {
        gc_thread.join();  // Esperar a que el hilo termine de manera segura
    }
}

// revisar punteros periódicamente
void MPointerGC::GarbageCollectorTask() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Revisa el mapa de punteros y eliminar aquellos con referencia 0
        for (auto it = pointer_map.begin(); it != pointer_map.end();) {
            if (it->second.second == 0) {
                delete static_cast<char*>(it->second.first);  // Liberar la memoria
                it = pointer_map.erase(it);  // Eliminar la entrada del mapa
            } else {
                ++it;
            }
        }
    }
}
