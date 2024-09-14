cmake_minimum_required(VERSION 3.20)
project(MPointerProject)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

if(UNIX)
    target_link_libraries(tests pthread)
endif()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include_directories(${GTEST_INCLUDE_DIRS})


set(SOURCES
        MPointer.cpp
        GarbageCollector.cpp
        Nodo.cpp
        ListaEnlazada.cpp
        Ordenamientos.cpp
        main.cpp
)


set(HEADERS
        MPointer.h
        GarbageCollector.h
        Nodo.h
        ListaEnlazada.h
        Ordenamientos.h
        main.cpp
)

add_executable(MPointerExecutable ${SOURCES} ${HEADERS})


add_executable(tests MPointerTests.cpp)
target_link_libraries(tests gtest gtest_main)


add_test(NAME MPointerTests COMMAND tests)

