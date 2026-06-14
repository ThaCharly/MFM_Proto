#pragma once
#include "../ActionDist.hpp"
#include "../ContextExtractor.hpp"

namespace mfm {

// Señal 6 de 7: Urgencia por marcador y momento.
// Pregunta: ¿Qué necesita el resultado? ¿Y cuánto tiempo queda?
// La urgencia solo activa en LATE y FINAL_MINUTES. En EARLY y MID el resultado
// todavía no cambia el estilo de juego de forma radical.
struct ScoreUrgencySignal {
    static void apply(ActionDist& dist, const Context& ctx) {
        const bool urgent = (ctx.moment == MatchMoment::LATE ||
                             ctx.moment == MatchMoment::FINAL_MINUTES);
        if (!urgent) return;

        switch (ctx.score_context) {
            case ScoreContext::LOSING_COMFORTABLE:
                // Todo o nada. El equipo busca el milagro.
                dist[A(ActionId::SHOOT)]      *= 2.0f;
                dist[A(ActionId::LONG_BALL)]  *= 1.8f;
                dist[A(ActionId::PASS_RISKY)] *= 1.6f;
                dist[A(ActionId::HOLD)]       *= 0.3f;
                dist[A(ActionId::PASS_SAFE)]  *= 0.5f;
                break;
            case ScoreContext::LOSING_TIGHT:
                // Busca el empate con más verticalidad, sin desesperarse aún.
                dist[A(ActionId::PASS_RISKY)] *= 1.4f;
                dist[A(ActionId::SHOOT)]      *= 1.3f;
                break;
            case ScoreContext::WINNING_COMFORTABLE:
                // Cerrar el partido. Circular, retener, no regalar nada.
                dist[A(ActionId::PASS_SAFE)]  *= 1.5f;
                dist[A(ActionId::HOLD)]       *= 1.6f;
                dist[A(ActionId::PASS_RISKY)] *= 0.5f;
                dist[A(ActionId::SHOOT)]      *= 0.7f;
                break;
            case ScoreContext::WINNING_TIGHT:
            case ScoreContext::LEVEL:
                break; // sin modificación, la base y el contexto ya manejan esto
        }
    }
};

} // namespace mfm