#pragma once
#include "../ActionDist.hpp"
#include "../ContextExtractor.hpp"
#include "../Tactics.hpp"
#include "../Weights.hpp"

namespace mfm {

// Señal 3 de 7: Instrucciones del DT.
// Pregunta: ¿Qué guion táctico impone el técnico en este momento?
// Incluye tanto el estilo de construcción como el modo de transición.
struct TacticsSignal {
    static void apply(ActionDist& dist, const TacticsProfile& tactics, const Context& ctx) {
        // Estilo de construcción (filosofía permanente del equipo)
        switch (tactics.build_up) {
            case BuildUpStyle::DIRECT:
                dist[A(ActionId::PASS_RISKY)] *= Weights::tacticDirectPassRisky();
                break;
            case BuildUpStyle::LONG_BALL:
                dist[A(ActionId::LONG_BALL)] *= Weights::tacticLongLongBall();
                break;
            default:
                break;
        }

        // Transición ofensiva (activa solo en los primeros ciclos tras recuperar)
        if (ctx.on_transition && tactics.atk_transition == TransitionStyle::FAST_BREAK) {
            dist[A(ActionId::PASS_RISKY)] *= Weights::transFastPassRisky();
            dist[A(ActionId::DRIBBLE)]    *= Weights::transFastDribble();
        }
    }
};

} // namespace mfm