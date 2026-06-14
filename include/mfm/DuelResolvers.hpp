#pragma once
#include "Match.hpp"
#include "ActionTypes.hpp"
#include "ContextExtractor.hpp"
#include "Random.hpp"
#include "Weights.hpp"
#include <string>
#include <algorithm>

namespace mfm {

// El resultado estandarizado de cualquier micro-duelo.
// El StateUpdater consumirá esto a ciegas para actualizar el partido.
struct ResolutionResult {
    bool success;
    ZoneId new_zone;
    TeamId new_possession;
    size_t new_carrier_idx;
    std::string description; // Texto formateado para el Logger
};

namespace resolvers {
    
    // --- HELPERS INLINE --- 
    // Funciones de utilidad rápida para no duplicar código en los resolvers.

    // Calcula el penalizador físico. A más fatiga, peores stats.
    inline float getFatigueModifier(const Match& match, TeamId team, int line) {
        float fatigue = (team == TeamId::HOME) ? match.state.fatigue_home[line] : match.state.fatigue_away[line];
        return std::max(Weights::fatigueMaxPenalty(), 1.0f - (fatigue / Weights::fatigueScale())); 
    }

    // Selecciona un defensor al azar basándose en la zona del campo.
    inline size_t pickDefenderIndex(ZoneClass zc) {
        if (zc == ZoneClass::DEFENSIVE) return RNG::range(8, 10); // Presionan los delanteros
        if (zc == ZoneClass::TRANSITION) return RNG::range(4, 7); // Cortan los volantes
        return RNG::range(1, 4); // Defienden los zagueros/laterales
    }

    // --- INTERFACES DE RESOLUCIÓN ---
    ResolutionResult resolvePass(const Match& match, const Team& attackers, const Team& defenders, ActionId action, const Context& ctx);
    ResolutionResult resolveDribble(const Match& match, const Team& attackers, const Team& defenders, ActionId action, const Context& ctx);
    ResolutionResult resolveShoot(const Match& match, const Team& attackers, const Team& defenders, ActionId action, const Context& ctx);

} // namespace resolvers
} // namespace mfm