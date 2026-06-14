#pragma once
#include <cstdint>

namespace mfm {

// Plantilla posicional base. Define densidades y líneas de pase por defecto.
enum class FormationId : uint8_t {
    F_433,
    F_442,
    F_352
};

// Define la agresividad sin pelota. Modifica la fatiga y el índice de presión rival.
enum class PressStyle : uint8_t {
    LOW_BLOCK,
    MID_BLOCK,
    HIGH_PRESS,
    GEGENPRESSING
};

// Define la filosofía con pelota.
enum class BuildUpStyle : uint8_t {
    PATIENT,   // Pondera posesión y pase seguro.
    DIRECT,    // Busca verticalidad y pase arriesgado.
    LONG_BALL, // Saltea el mediocampo sistemáticamente.
    TIKI_TAKA  // TOQUE Y TOQUE MIERDA! 
};

// Define la reacción inmediata (los primeros 5-10 segundos) al cambio de posesión.
enum class TransitionStyle : uint8_t {
    FAST_BREAK,      // Ataque: Salir disparado hacia adelante.
    CONTROLLED,      // Ataque: Asegurar el primer pase y armar.
    DELAYED,         // Ataque: Pisar la pelota y esperar que suban las líneas.
    IMMEDIATE_PRESS, // Defensa: Morder apenas se pierde.
    REGROUP          // Defensa: Correr para atrás y armar las dos líneas de 4.
};

// El bloque de instrucciones completo que recibe el motor para el equipo.
struct TacticsProfile {
    PressStyle press_style;
    BuildUpStyle build_up;
    TransitionStyle atk_transition;
    TransitionStyle def_transition;
    float defensive_line; // Rango [0.0, 1.0]. 1.0 es jugar en la mitad de la cancha.
    float width;          // Rango [0.0, 1.0]. 1.0 es abrir la cancha al máximo.
};

} // namespace mfm