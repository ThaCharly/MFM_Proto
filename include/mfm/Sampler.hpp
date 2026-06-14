#pragma once
#include "ActionTypes.hpp"
#include <array>

namespace mfm {

// Ejecuta la Ruleta Rusa estadística.
class Sampler {
public:
    // Recibe un array normalizado (suma 1.0) y selecciona una acción usando RNG.
    static ActionId sample(const std::array<float, static_cast<size_t>(ActionId::ACTION_COUNT)>& dist);
};

} // namespace mfm