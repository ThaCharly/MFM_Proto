#pragma once
#include <random>
#include <cstdint>

namespace mfm {

// Singleton estático para garantizar el determinismo en toda la simulación.
// Se le inyecta la semilla una sola vez en el main y todos los módulos consumen de acá.
class RNG {
public:
    // Fija el punto de partida del generador Mersenne Twister.
    static void seed(uint32_t seedValue) {
        getEngine().seed(seedValue);
    }

    // Retorna probabilidad pura: [0.0, 1.0)
    static double random() {
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(getEngine());
    }

    // Retorna un valor entero inclusivo [min, max]. Útil para índices de arrays.
    static int range(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(getEngine());
    }

private:
    static std::mt19937& getEngine() {
        static std::mt19937 engine;
        return engine;
    }
};

} // namespace mfm