#include "mfm/Sampler.hpp"
#include "mfm/Random.hpp"

namespace mfm {

ActionId Sampler::sample(const std::array<float, static_cast<size_t>(ActionId::ACTION_COUNT)>& dist) {
    // Generamos un número aleatorio entre 0.0 y 1.0
    double r = RNG::random();
    
    // Algoritmo de Ruleta (Roulette Wheel Selection)
    // Va sumando las probabilidades hasta "chocar" con el número aleatorio.
    double accumulator = 0.0;
    
    for (size_t i = 0; i < dist.size(); ++i) {
        accumulator += dist[i];
        if (r <= accumulator) {
            return static_cast<ActionId>(i);
        }
    }
    
    // Seguro de flotantes: si falla por redondeo (99.99%), devuelve la última acción válida.
    return ActionId::PASS_SAFE; 
}

} // namespace mfm