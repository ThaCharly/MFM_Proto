#include "mfm/InferenceEngine.hpp"
#include "mfm/Weights.hpp"

namespace mfm {

std::array<float, static_cast<size_t>(ActionId::ACTION_COUNT)> 
InferenceEngine::infer(const Context& ctx, const PlayerProfile& carrier, const TacticsProfile& tactics) {
    std::array<float, static_cast<size_t>(ActionId::ACTION_COUNT)> dist{};
    dist.fill(Weights::baseActionProb()); // Suavizado base dinámico

    // 1. Cimientos por Zona (Qué te pide la cancha)
    switch (ctx.zone_class) {
        case ZoneClass::DEFENSIVE:
            dist[static_cast<size_t>(ActionId::PASS_SAFE)] = Weights::zoneDefPassSafe();
            dist[static_cast<size_t>(ActionId::LONG_BALL)] = Weights::zoneDefLongBall();
            dist[static_cast<size_t>(ActionId::HOLD)]      = Weights::zoneDefHold();
            break;
        case ZoneClass::TRANSITION:
            dist[static_cast<size_t>(ActionId::PASS_SAFE)]  = Weights::zoneTransPassSafe();
            dist[static_cast<size_t>(ActionId::PASS_RISKY)] = Weights::zoneTransPassRisky();
            dist[static_cast<size_t>(ActionId::DRIBBLE)]    = Weights::zoneTransDribble();
            break;
        case ZoneClass::OFFENSIVE:
            dist[static_cast<size_t>(ActionId::PASS_RISKY)] = Weights::zoneOffPassRisky();
            dist[static_cast<size_t>(ActionId::CROSS)]      = Weights::zoneOffCross();
            dist[static_cast<size_t>(ActionId::DRIBBLE)]    = Weights::zoneOffDribble();
            break;
        case ZoneClass::DANGER_AREA:
            dist[static_cast<size_t>(ActionId::SHOOT)]      = Weights::zoneDangerShoot();
            dist[static_cast<size_t>(ActionId::PASS_SAFE)]  = Weights::zoneDangerPassSafe();
            break;
    }

    // 2. Sesgos por Rol (La naturaleza del jugador)
    if (carrier.role == RoleId::GOALKEEPER) {
        dist[static_cast<size_t>(ActionId::LONG_BALL)] *= Weights::roleGkLongBall();
    } else if (carrier.role == RoleId::TARGET_FORWARD) {
        dist[static_cast<size_t>(ActionId::HOLD)]  *= Weights::roleTargetManHold();
    }

    // 3. Modificadores del DT (El guion táctico)
    if (tactics.build_up == BuildUpStyle::DIRECT) {
        dist[static_cast<size_t>(ActionId::PASS_RISKY)] *= Weights::tacticDirectPassRisky();
    } else if (tactics.build_up == BuildUpStyle::LONG_BALL) {
        dist[static_cast<size_t>(ActionId::LONG_BALL)] *= Weights::tacticLongLongBall();
    }

    // 4. Modo Emergencia (El equipo recuperó la pelota recién)
    if (ctx.on_transition && tactics.atk_transition == TransitionStyle::FAST_BREAK) {
        dist[static_cast<size_t>(ActionId::PASS_RISKY)] *= Weights::transFastPassRisky();
        dist[static_cast<size_t>(ActionId::DRIBBLE)]    *= Weights::transFastDribble();
    }

    // Apagar acciones defensivas si tenemos la posesión.
    dist[static_cast<size_t>(ActionId::PRESS)] = 0.0f;
    dist[static_cast<size_t>(ActionId::TACKLE)] = 0.0f;
    dist[static_cast<size_t>(ActionId::INTERCEPT)] = 0.0f;

    // Normalización: Asegurar que la suma de todas las probabilidades sea exactamente 1.0
    float sum = 0.0f;
    for (float w : dist) sum += w;
    if (sum > 0.0f) {
        for (float& w : dist) w /= sum;
    } else {
        // Fallback matemático de seguridad.
        dist[static_cast<size_t>(ActionId::PASS_SAFE)] = 1.0f;
    }

    return dist;
}

} // namespace mfm