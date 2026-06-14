#pragma once
#include "../ActionDist.hpp"
#include "../ContextExtractor.hpp"
#include "../Weights.hpp"

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
                dist[A(ActionId::PASS_SAFE)]  *= Weights::lane0PassSafe();
                dist[A(ActionId::PASS_RISKY)]  = Weights::lane0PassRisky();
                dist[A(ActionId::HOLD)]       *= Weights::lane0Hold();
                dist[A(ActionId::DRIBBLE)]    *= Weights::lane0Dribble();
                break;
            case 1:
                // Un solo carril: el pase riesgoso es muy forzado
                dist[A(ActionId::PASS_RISKY)] *= Weights::lane1PassRisky();
                dist[A(ActionId::PASS_SAFE)]  *= Weights::lane1PassSafe();
                break;
            default:
                break; // 2+ carriles: distribución base es correcta
        }
    }
};

} // namespace mfm