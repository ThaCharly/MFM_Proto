#pragma once
#include "../ActionDist.hpp"
#include "../ContextExtractor.hpp"

namespace mfm {

// Bonus signal: Líneas de pase disponibles.
// Pregunta: ¿Hay a quién pasarle?
// ctx.passing_lanes está poblado por ContextExtractor pero ignorado en infer.
// Si no hay carriles, el pase riesgoso desaparece como opción real.
struct PassingLanesSignal {
    static void apply(ActionDist& dist, const Context& ctx) {
        switch (ctx.passing_lanes) {
            case 0:
                // Sin salida: retener o gambetear es la única opción honesta
                dist[A(ActionId::PASS_SAFE)]  *= 0.3f;
                dist[A(ActionId::PASS_RISKY)]  = 0.0f;
                dist[A(ActionId::HOLD)]       *= 2.0f;
                dist[A(ActionId::DRIBBLE)]    *= 1.5f;
                break;
            case 1:
                // Un solo carril: el pase riesgoso es muy forzado
                dist[A(ActionId::PASS_RISKY)] *= 0.5f;
                dist[A(ActionId::PASS_SAFE)]  *= 0.8f;
                break;
            default:
                break; // 2+ carriles: distribución base es correcta
        }
    }
};

} // namespace mfm