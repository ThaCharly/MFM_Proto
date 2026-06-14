#pragma once
#include "../ActionDist.hpp"
#include "../Player.hpp"
#include "../Weights.hpp"

namespace mfm {

// Señal 2 de 7: Sesgos por rol.
// Pregunta: ¿Cuál es la naturaleza táctica de este jugador?
// Opera con multiplicación (*=) sobre la base que puso ZoneSignal.
struct RoleSignal {
    static void apply(ActionDist& dist, const PlayerProfile& carrier) {
        switch (carrier.role) {
            case RoleId::GOALKEEPER:
                dist[A(ActionId::LONG_BALL)] *= Weights::roleGkLongBall();
                break;
            case RoleId::TARGET_FORWARD:
                dist[A(ActionId::HOLD)] *= Weights::roleTargetManHold();
                break;
            default:
                break;
        }
    }
};

} // namespace mfm