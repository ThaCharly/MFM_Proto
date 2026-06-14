#pragma once
#include "../ActionDist.hpp"
#include "../ContextExtractor.hpp"
#include "../Weights.hpp"

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
                dist[A(ActionId::SHOOT)]      *= Weights::urgLoseComfShoot();
                dist[A(ActionId::LONG_BALL)]  *= Weights::urgLoseComfLongBall();
                dist[A(ActionId::PASS_RISKY)] *= Weights::urgLoseComfPassRisky();
                dist[A(ActionId::HOLD)]       *= Weights::urgLoseComfHold();
                dist[A(ActionId::PASS_SAFE)]  *= Weights::urgLoseComfPassSafe();
                break;
            case ScoreContext::LOSING_TIGHT:
                // Busca el empate con más verticalidad, sin desesperarse aún.
                dist[A(ActionId::PASS_RISKY)] *= Weights::urgLoseTightPassRisky();
                dist[A(ActionId::SHOOT)]      *= Weights::urgLoseTightShoot();
                break;
            case ScoreContext::WINNING_COMFORTABLE:
                // Cerrar el partido. Circular, retener, no regalar nada.
                dist[A(ActionId::PASS_SAFE)]  *= Weights::urgWinComfPassSafe();
                dist[A(ActionId::HOLD)]       *= Weights::urgWinComfHold();
                dist[A(ActionId::PASS_RISKY)] *= Weights::urgWinComfPassRisky();
                dist[A(ActionId::SHOOT)]      *= Weights::urgWinComfShoot();
                break;
            case ScoreContext::WINNING_TIGHT:
            case ScoreContext::LEVEL:
                break; // sin modificación, la base y el contexto ya manejan esto
        }
    }
};

} // namespace mfm