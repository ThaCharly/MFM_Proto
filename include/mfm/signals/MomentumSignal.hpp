#pragma once
#include "../ActionDist.hpp"

namespace mfm {

// Señal 5 de 7: Momentum del partido.
// Pregunta: ¿El equipo viene de más o de menos?
// state.momentum ∈ [-1.0, 1.0]. Positivo = favorece al equipo con posesión.
// Con momentum alto el equipo se anima a más. Con momentum negativo, cierra filas.
// Nota: el caller normaliza el signo según qué equipo tiene la pelota.
struct MomentumSignal {
    static void apply(ActionDist& dist, float momentum) {
        if (momentum > 0.5f) {
            dist[A(ActionId::PASS_RISKY)] *= 1.3f;
            dist[A(ActionId::DRIBBLE)]    *= 1.2f;
            dist[A(ActionId::SHOOT)]      *= 1.15f;
        } else if (momentum < -0.5f) {
            dist[A(ActionId::HOLD)]       *= 1.4f;
            dist[A(ActionId::PASS_SAFE)]  *= 1.3f;
            dist[A(ActionId::PASS_RISKY)] *= 0.6f;
        }
        // [-0.5, 0.5]: momentum neutro, no interferir
    }
};

} // namespace mfm