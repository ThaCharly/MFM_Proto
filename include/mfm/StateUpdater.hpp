#pragma once
#include "Match.hpp"
#include "ActionTypes.hpp"
#include "DuelResolvers.hpp"

namespace mfm {

// Motor de mutación de estado. Aplica las decisiones matemáticas de forma agnóstica.
class StateUpdater {
public:
    // Delega el registro al StatsTracker, muta el GameState (zona, portador, posesión),
    // y dispara el avance del reloj y desgaste físico.
    static void applyResolution(
        Match& match, 
        ActionId action, 
        const ResolutionResult& res
    );

private:
    // Funciones de uso estrictamente interno.
    static void advanceTime(Match& match, float dt);
    
    // Acumula desgaste según la acción y el estilo de juego activo.
    static void accumulateFatigue(Match& match, float dt);
};

} // namespace mfm