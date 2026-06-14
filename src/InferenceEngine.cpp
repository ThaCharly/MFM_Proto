#include "mfm/InferenceEngine.hpp"
#include "mfm/Config.hpp"

namespace mfm {

std::array<float, static_cast<size_t>(ActionId::ACTION_COUNT)> 
InferenceEngine::infer(const Context& ctx, const PlayerProfile& carrier, const TacticsProfile& tactics) {
    auto& cfg = Config::getInstance();
    
    std::array<float, static_cast<size_t>(ActionId::ACTION_COUNT)> dist{};
    dist.fill(cfg.get("BASE_ACTION_PROB", 0.01f)); // Suavizado base dinámico

    // 1. Cimientos por Zona (Qué te pide la cancha)
    switch (ctx.zone_class) {
        case ZoneClass::DEFENSIVE:
            dist[static_cast<size_t>(ActionId::PASS_SAFE)] = cfg.get("ZONE_DEF_PASS_SAFE", 0.60f);
            dist[static_cast<size_t>(ActionId::LONG_BALL)] = cfg.get("ZONE_DEF_LONG_BALL", 0.25f);
            dist[static_cast<size_t>(ActionId::HOLD)]      = cfg.get("ZONE_DEF_HOLD", 0.10f);
            break;
        case ZoneClass::TRANSITION:
            dist[static_cast<size_t>(ActionId::PASS_SAFE)]  = cfg.get("ZONE_TRANS_PASS_SAFE", 0.50f);
            dist[static_cast<size_t>(ActionId::PASS_RISKY)] = cfg.get("ZONE_TRANS_PASS_RISKY", 0.20f);
            dist[static_cast<size_t>(ActionId::DRIBBLE)]    = cfg.get("ZONE_TRANS_DRIBBLE", 0.15f);
            break;
        case ZoneClass::OFFENSIVE:
            dist[static_cast<size_t>(ActionId::PASS_RISKY)] = cfg.get("ZONE_OFF_PASS_RISKY", 0.35f);
            dist[static_cast<size_t>(ActionId::CROSS)]      = cfg.get("ZONE_OFF_CROSS", 0.20f);
            dist[static_cast<size_t>(ActionId::DRIBBLE)]    = cfg.get("ZONE_OFF_DRIBBLE", 0.20f);
            break;
        case ZoneClass::DANGER_AREA:
            dist[static_cast<size_t>(ActionId::SHOOT)]      = cfg.get("ZONE_DANGER_SHOOT", 0.60f);
            dist[static_cast<size_t>(ActionId::PASS_SAFE)]  = cfg.get("ZONE_DANGER_PASS_SAFE", 0.15f);
            break;
    }

    // 2. Sesgos por Rol (La naturaleza del jugador)
    if (carrier.role == RoleId::GOALKEEPER) {
        dist[static_cast<size_t>(ActionId::LONG_BALL)] *= cfg.get("ROLE_GK_LONG_BALL", 3.0f);
    } else if (carrier.role == RoleId::TARGET_FORWARD) {
        dist[static_cast<size_t>(ActionId::HOLD)]  *= cfg.get("ROLE_TARGET_MAN_HOLD", 3.5f);
    }

    // 3. Modificadores del DT (El guion táctico)
    if (tactics.build_up == BuildUpStyle::DIRECT) {
        dist[static_cast<size_t>(ActionId::PASS_RISKY)] *= cfg.get("TACTIC_DIRECT_PASS_RISKY", 1.6f);
    } else if (tactics.build_up == BuildUpStyle::LONG_BALL) {
        dist[static_cast<size_t>(ActionId::LONG_BALL)] *= cfg.get("TACTIC_LONG_LONG_BALL", 2.5f);
    }

    // 4. Modo Emergencia (El equipo recuperó la pelota recién)
    if (ctx.on_transition && tactics.atk_transition == TransitionStyle::FAST_BREAK) {
        dist[static_cast<size_t>(ActionId::PASS_RISKY)] *= cfg.get("TRANS_FAST_PASS_RISKY", 2.0f);
        dist[static_cast<size_t>(ActionId::DRIBBLE)]    *= cfg.get("TRANS_FAST_DRIBBLE", 1.5f);
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