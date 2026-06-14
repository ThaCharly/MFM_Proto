#include "mfm/InferenceEngine.hpp"
#include "mfm/Weights.hpp"
#include "mfm/signals/ZoneSignal.hpp"
#include "mfm/signals/RoleSignal.hpp"
#include "mfm/signals/TacticsSignal.hpp"
#include "mfm/signals/PressureSignal.hpp"
#include "mfm/signals/MomentumSignal.hpp"
#include "mfm/signals/ScoreUrgencySignal.hpp"
#include "mfm/signals/AttributeSignal.hpp"
#include "mfm/signals/PassingLanesSignal.hpp"
#include "mfm/signals/ConsecutivePassesSignal.hpp"

namespace mfm {

ActionDist InferenceEngine::infer(
    const Context&        ctx,
    const PlayerProfile&  carrier,
    const TacticsProfile& tactics,
    const GameState&      state
) {
    ActionDist dist{};
    dist.fill(Weights::baseActionProb()); // suavizado base: ninguna acción arranca en 0

    // --- CAPA 1: QUÉ TE PIDE LA CANCHA ---
    ZoneSignal::apply(dist, ctx);

    // --- CAPA 2: QUIÉN ERES ---
    RoleSignal::apply(dist, carrier);

    // --- CAPA 3: QUÉ ORDENA EL DT ---
    TacticsSignal::apply(dist, tactics, ctx);

    // --- CAPA 4: QUÉ DICE EL CONTEXTO DEL PARTIDO ---
    PressureSignal::apply(dist, ctx);
    MomentumSignal::apply(dist, state.momentum);
    ScoreUrgencySignal::apply(dist, ctx);
    ConsecutivePassesSignal::apply(dist, state.consecutive_passes);
    PassingLanesSignal::apply(dist, ctx);

    // --- CAPA 5: CÓMO PERCIBE EL MUNDO ESTE JUGADOR ---
    AttributeSignal::apply(dist, carrier);

    // Apagar acciones sin posesión
    dist[A(ActionId::PRESS)]     = 0.0f;
    dist[A(ActionId::TACKLE)]    = 0.0f;
    dist[A(ActionId::INTERCEPT)] = 0.0f;

    // Normalización: la suma de todos los pesos debe ser exactamente 1.0
    float sum = 0.0f;
    for (float w : dist) sum += w;
    if (sum > 0.0f) {
        for (float& w : dist) w /= sum;
    } else {
        dist[A(ActionId::PASS_SAFE)] = 1.0f; // fallback matemático de seguridad
    }

    return dist;
}

} // namespace mfm