#pragma once
#include <cstdint>
#include <string_view>

namespace mfm {

// Enumeración estricta de las acciones que puede tomar un jugador.
// Separamos la decisión (inferencia) de la resolución (ejecución).
enum class ActionId : uint8_t {
    PASS_SAFE = 0,
    PASS_RISKY,
    LONG_BALL,
    DRIBBLE,
    HOLD,
    CROSS,
    SHOOT,
    SHOOT_LONG,
    
    // Acciones sin pelota (Se usarán en la Fase 4 para los defensores)
    PRESS,
    RECOVER_POSITION,
    INTERCEPT,
    TACKLE,
    
    ACTION_COUNT // Centinela estático para dimensionar arrays (ej: std::array)
};

// Traductor rápido para los logs de la consola y debugging.
inline std::string_view actionToString(ActionId action) {
    switch (action) {
        case ActionId::PASS_SAFE:  return "Pase Seguro";
        case ActionId::PASS_RISKY: return "Pase Arriesgado";
        case ActionId::LONG_BALL:  return "Pelotazo Largo";
        case ActionId::DRIBBLE:    return "Gambeta";
        case ActionId::HOLD:       return "Retención";
        case ActionId::CROSS:      return "Centro";
        case ActionId::SHOOT:      return "Tiro a Puerta";
        case ActionId::SHOOT_LONG: return "Tiro Lejano";
        default:                   return "Accion Desconocida";
    }
}

} // namespace mfm