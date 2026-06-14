#pragma once
#include "ActionTypes.hpp"
#include "ContextExtractor.hpp"
#include "Player.hpp"
#include "Tactics.hpp"
#include <array>

namespace mfm {

// Motor estocástico. NO lanza los dados, solo arma las probabilidades matemáticas (Matriz P).
class InferenceEngine {
public:
    // Retorna un array donde el índice es la Acción, y el valor es su probabilidad [0.0, 1.0]
    static std::array<float, static_cast<size_t>(ActionId::ACTION_COUNT)> 
    infer(const Context& ctx, const PlayerProfile& carrier, const TacticsProfile& tactics);
};

} // namespace mfm