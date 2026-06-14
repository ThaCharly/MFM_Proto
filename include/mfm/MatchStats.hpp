#pragma once
#include <cstdint>

namespace mfm {

// Registro histórico del partido. 
// Solo se incrementa, jamás se lee para tomar decisiones dentro de la cancha.
struct MatchStats {
    uint16_t goals_home = 0;
    uint16_t goals_away = 0;
    
    uint16_t passes_attempted_home = 0;
    uint16_t passes_success_home = 0;
    uint16_t passes_attempted_away = 0;
    uint16_t passes_success_away = 0;
    
    uint16_t shots_on_target_home = 0;
    uint16_t shots_off_target_home = 0;
    uint16_t shots_on_target_away = 0;
    uint16_t shots_off_target_away = 0;
    
    uint16_t saves_home = 0;
    uint16_t saves_away = 0;
    
    uint16_t interceptions_home = 0;
    uint16_t interceptions_away = 0;
    
    uint16_t tackles_home = 0;
    uint16_t tackles_away = 0;
};

} // namespace mfm