#pragma once
#include "Types.hpp"
#include <cstddef>

namespace mfm {

// La foto exacta del partido en el milisegundo actual.
// Este es el único struct que se muta constantemente en el SimulationLoop.
struct GameState {
    int minute = 0;
    int second = 0;
    
    TeamId possession = TeamId::HOME;
    ZoneId ball_zone = ZoneId::MID_C;
    size_t ball_carrier_idx = 6; // Apunta al índice (0-10) del vector 'squad' del equipo con posesión.
    
    GamePhase phase = GamePhase::OPEN_PLAY;
    
    // Variables de contexto emergente (La historia reciente de la jugada).
    float pressure_index = 0.1f; // [0.0, 1.0]: Aumenta con pases exitosos y densidad defensiva.
    float momentum = 0.0f;       // [-1.0, 1.0]: Favorece a HOME (+) o AWAY (-). Afecta la moral.
    uint8_t consecutive_passes = 0;
    
    // Matriz de desgaste físico real, separado por líneas tácticas (GK, DEF, MID, ATK).
    // Impacta negativamente como penalizador en todas las matemáticas de resolución de duelos.
    float fatigue_home[4] = {0.0f, 0.0f, 0.0f, 0.0f}; 
    float fatigue_away[4] = {0.0f, 0.0f, 0.0f, 0.0f};
};

} // namespace mfm