#pragma once
#include "../ActionDist.hpp"
#include "../ContextExtractor.hpp"
#include "../Weights.hpp"

namespace mfm {

// Señal 1 de 7: Cimientos por zona.
// Pregunta: ¿Qué te pide la cancha desde donde estás parado?
// Opera con asignación directa (=), no multiplicación (*=).
// Es la base sobre la que todas las demás señales multiplican.
struct ZoneSignal {
    static void apply(ActionDist& dist, const Context& ctx) {
        switch (ctx.zone_class) {
            case ZoneClass::DEFENSIVE:
                dist[A(ActionId::PASS_SAFE)] = Weights::zoneDefPassSafe();
                dist[A(ActionId::LONG_BALL)] = Weights::zoneDefLongBall();
                dist[A(ActionId::HOLD)]      = Weights::zoneDefHold();
                break;
            case ZoneClass::TRANSITION:
                dist[A(ActionId::PASS_SAFE)]  = Weights::zoneTransPassSafe();
                dist[A(ActionId::PASS_RISKY)] = Weights::zoneTransPassRisky();
                dist[A(ActionId::DRIBBLE)]    = Weights::zoneTransDribble();
                break;
            case ZoneClass::OFFENSIVE:
                dist[A(ActionId::PASS_RISKY)] = Weights::zoneOffPassRisky();
                dist[A(ActionId::CROSS)]      = Weights::zoneOffCross();
                dist[A(ActionId::DRIBBLE)]    = Weights::zoneOffDribble();
                break;
            case ZoneClass::DANGER_AREA:
                dist[A(ActionId::SHOOT)]     = Weights::zoneDangerShoot();
                dist[A(ActionId::PASS_SAFE)] = Weights::zoneDangerPassSafe();
                break;
        }
    }
};

} // namespace mfm