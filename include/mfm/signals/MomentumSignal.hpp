#pragma once
#include "../ActionDist.hpp"
#include "../Weights.hpp"

namespace mfm {

// Señal 5 de 7: Momentum del partido.
// Pregunta: ¿El equipo viene de más o de menos?
// state.momentum ∈ [-1.0, 1.0]. Positivo = favorece al equipo con posesión.
// Con momentum alto el equipo se anima a más. Con momentum negativo, cierra filas.
// Nota: el caller normaliza el signo según qué equipo tiene la pelota.
struct MomentumSignal {
    static void apply(ActionDist& dist, float momentum) {
        if (momentum > 0.5f) {
            dist[A(ActionId::PASS_RISKY)] *= Weights::momHighPassRisky();
            dist[A(ActionId::DRIBBLE)]    *= Weights::momHighDribble();
            dist[A(ActionId::SHOOT)]      *= Weights::momHighShoot();
        } else if (momentum < -0.5f) {
            dist[A(ActionId::HOLD)]       *= Weights::momLowHold();
            dist[A(ActionId::PASS_SAFE)]  *= Weights::momLowPassSafe();
            dist[A(ActionId::PASS_RISKY)] *= Weights::momLowPassRisky();
        }
        // [-0.5, 0.5]: momentum neutro, no interferir
    }
};

} // namespace mfm