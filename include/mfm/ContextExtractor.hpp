#pragma once
#include "GameState.hpp"
#include "MatchStats.hpp"
#include "Team.hpp"
#include "Match.hpp"

namespace mfm {

// Sub-estados emergentes que facilitan la toma de decisiones.
enum class PressureLevel : uint8_t { LOW, MEDIUM, HIGH, EXTREME };
enum class ScoreContext : uint8_t { WINNING_COMFORTABLE, WINNING_TIGHT, LEVEL, LOSING_TIGHT, LOSING_COMFORTABLE };
enum class MatchMoment : uint8_t { EARLY, MID, LATE, FINAL_MINUTES };
enum class FatigueLevel : uint8_t { FRESH, TIRED, EXHAUSTED };

// La abstracción del GameState. Esto es lo que el jugador "percibe" antes de actuar.
struct Context {
    ZoneId zone;
    ZoneClass zone_class;
    PressureLevel pressure;
    ScoreContext score_context;
    MatchMoment moment;
    FatigueLevel carrier_fatigue;
    bool on_transition;
    bool space_available;
    uint8_t passing_lanes;
};

// Convierte datos crudos (minuto 88, perdiendo 1-0) en contexto táctico (FINAL_MINUTES, LOSING_TIGHT).
class ContextExtractor {
public:
    static Context extract(
        const Match& match,
        const Team& home,
        const Team& away
    );
};

} // namespace mfm