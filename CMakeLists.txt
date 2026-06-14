cmake_minimum_required(VERSION 3.15)

# Nombre del proyecto
project(MFM_Engine VERSION 0.2 LANGUAGES CXX)

# Exigimos C++20 explícitamente (Clave para los Designated Initializers)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Le decimos al compilador dónde buscar los .hpp
include_directories(include)

# Agrupamos todos los archivos fuente limpios de nuestra arquitectura modular
set(SOURCES
    src/Config.cpp
    src/ContextExtractor.cpp
    src/InferenceEngine.cpp
    src/Sampler.cpp
    src/PassResolver.cpp
    src/DribbleResolver.cpp
    src/ShootResolver.cpp
    src/StateUpdater.cpp
    src/StatsTracker.cpp
    src/Logger.cpp
    src/SimulationLoop.cpp
    src/main.cpp
)

# Compilamos el ejecutable
add_executable(mfm_sim ${SOURCES})

# Opciones de compilación para que Ubuntu te avise de posibles errores de memoria/variables
target_compile_options(mfm_sim PRIVATE -Wall -Wextra -Wpedantic)