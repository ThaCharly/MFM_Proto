#pragma once
#include "ActionDist.hpp"
#include "ActionTypes.hpp"
#include "ContextExtractor.hpp"
#include "GameState.hpp"
#include "Player.hpp"
#include "Tactics.hpp"

namespace mfm {

// Motor estocástico. NO lanza los dados, solo arma las probabilidades matemáticas.
// Pipeline: ZoneSignal → RoleSignal → TacticsSignal → ContextSignal → AttributeSignal → Normalize
// Cada señal es independiente y opera sobre la misma ActionDist por referencia.
class InferenceEngine {
public:
    // Retorna la distribución de probabilidad sobre todas las acciones posibles.
    // La suma de todos los valores es exactamente 1.0 (post-normalización).
    // GameState se agrega para exponer momentum y consecutive_passes a las señales.
    static ActionDist infer(
        const Context&        ctx,
        const PlayerProfile&  carrier,
        const TacticsProfile& tactics,
        const GameState&      state
    );
};

} // namespace mfm