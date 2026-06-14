#pragma once
#include "ActionTypes.hpp"
#include <array>

namespace mfm {

// Alias central para la distribución de probabilidades de acción.
// Todos los signals y el InferenceEngine usan este tipo.
// El índice es ActionId casteado a size_t; el valor es un peso no normalizado [0.0, N].
using ActionDist = std::array<float, static_cast<size_t>(ActionId::ACTION_COUNT)>;

// Helper para no escribir el cast en cada acceso.
// Uso: dist[A(ActionId::PASS_SAFE)] en lugar de dist[static_cast<size_t>(ActionId::PASS_SAFE)]
inline constexpr size_t A(ActionId id) {
    return static_cast<size_t>(id);
}

} // namespace mfm