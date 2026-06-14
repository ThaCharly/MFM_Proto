#pragma once
#include <string>
#include <cstdint>

namespace mfm {

// Define el sesgo de comportamiento táctico en la cancha, independientemente de los stats.
enum class RoleId : uint8_t {
    GOALKEEPER,
    CENTER_BACK,
    DEFENSIVE_FULLBACK,
    OFFENSIVE_FULLBACK,
    DEFENSIVE_MIDFIELDER,
    BOX_TO_BOX,
    DEEP_LYING_PLAYMAKER,
    ADVANCED_PLAYMAKER,
    WINGER,
    TARGET_FORWARD,
    PRESSING_FORWARD,
    INSIDE_FORWARD
};

// Todos los stats van de 1 a 100. Modifican la tasa de éxito (resolve), NO la decisión (infer).
struct PlayerAttributes {
    uint8_t passing;
    uint8_t first_touch;
    uint8_t dribbling;
    uint8_t shooting;
    uint8_t heading;
    uint8_t crossing;
    uint8_t vision;       // Permite ver líneas de pase complejas.
    uint8_t positioning;  // Clave en defensa para interceptar.
    uint8_t anticipation; // Tiempo de reacción frente a decisiones rivales.
    uint8_t composure;    // Amortigua los errores cuando la presión táctica es alta.
    uint8_t pace;
    uint8_t stamina;      // Reduce la acumulación de fatiga por ciclo.
    uint8_t strength;     // Duelos físicos (ej. retener el balón de espaldas).
    uint8_t tackling;
    uint8_t marking;
    uint8_t reflexes_gk;
    uint8_t positioning_gk;
    uint8_t handling_gk;
    uint8_t aerial_gk;
};

// La ficha técnica inmutable del jugador.
struct PlayerProfile {
    std::string name;
    RoleId role;
    PlayerAttributes attrs;
    int line; // Agrupación física: 0=GK, 1=DEF, 2=MID, 3=ATK.
};

} // namespace mfm