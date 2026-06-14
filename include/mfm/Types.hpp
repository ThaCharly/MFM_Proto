#pragma once
#include <cstdint>

namespace mfm {

// Identificador absoluto para saber de quién es la pelota o el evento.
enum class TeamId : uint8_t {
    HOME = 0,
    AWAY = 1,
    NONE = 2 // Útil para balones divididos o eventos de sistema (ej. pitazo inicial).
};

// Discretización espacial del campo. 12 zonas para simplificar la matemática posicional.
enum class ZoneId : uint8_t {
    DEF_L = 0, DEF_C, DEF_R, // Campo propio defensivo
    MID_L,     MID_C, MID_R, // Mediocampo propio/neutro
    ATK_L,     ATK_C, ATK_R, // 3/4 de cancha
    BOX_L,     BOX_C, BOX_R, // Área y peligro inminente
    ZONE_COUNT = 12
};

// Clasificación semántica de la zona para el motor de inferencia táctica.
enum class ZoneClass : uint8_t {
    DEFENSIVE,
    TRANSITION,
    OFFENSIVE,
    DANGER_AREA
};

// El estado macro del juego, dicta qué reglas y tiempos se aplican.
enum class GamePhase : uint8_t {
    OPEN_PLAY,      // Juego rodando normal.
    SET_PIECE,      // Pelota parada (córner, tiro libre, saque de arco).
    TRANSITION_ATK, // Segundos posteriores a recuperar la guinda.
    TRANSITION_DEF  // Segundos posteriores a perderla.
};

} // namespace mfm
