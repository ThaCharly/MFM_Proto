#include "mfm/SimulationLoop.hpp"
#include "mfm/ContextExtractor.hpp"
#include "mfm/InferenceEngine.hpp"
#include "mfm/Sampler.hpp"
#include "mfm/DuelResolvers.hpp"
#include "mfm/StateUpdater.hpp"
#include "mfm/Logger.hpp"
#include "mfm/Random.hpp"
#include <thread>
#include <chrono>

namespace mfm {

Match SimulationLoop::run(const Team& home, const Team& away, uint32_t seed, bool verbose) {
    // 1. Inicializamos el azar y el estado en blanco.
    RNG::seed(seed);
    Match match{};
    
    if (verbose) {
        ResolutionResult kickoff{true, ZoneId::MID_C, TeamId::HOME, 6, "Arranca el partido, mueve el local."};
        Logger::logEvent(match, kickoff);
    }

    // 2. Bucle Core
    while (!isFinished(match)) {
        // FASE 3: Analizar e Inferir
        Context ctx = ContextExtractor::extract(match, home, away);
        const Team& attackers = (match.state.possession == TeamId::HOME) ? home : away;
        const Team& defenders = (match.state.possession == TeamId::HOME) ? away : home;
        const PlayerProfile& carrier = attackers.squad[match.state.ball_carrier_idx];
        
        auto dist = InferenceEngine::infer(ctx, carrier, attackers.tactics, match.state);
        ActionId action = Sampler::sample(dist);
        
        // FASE 4: Resolver la física del duelo
        ResolutionResult res;
        if (action == ActionId::PASS_SAFE || action == ActionId::PASS_RISKY || action == ActionId::LONG_BALL || action == ActionId::CROSS) {
            res = resolvers::resolvePass(match, attackers, defenders, action, ctx);
        } else if (action == ActionId::DRIBBLE || action == ActionId::HOLD) {
            res = resolvers::resolveDribble(match, attackers, defenders, action, ctx);
        } else if (action == ActionId::SHOOT || action == ActionId::SHOOT_LONG) {
            res = resolvers::resolveShoot(match, attackers, defenders, action, ctx);
        } else {
            // Acción defensiva o sin pelota (Fallback de seguridad)
            res = {true, ctx.zone, match.state.possession, match.state.ball_carrier_idx, "Mueve la pelota en su zona."};
        }

        // FASE 5: Aplicar consecuencias
        StateUpdater::applyResolution(match, action, res);

        // FASE 6: Loggear e interactuar
        if (verbose) {
            Logger::logEvent(match, res);
            
            if ((action == ActionId::SHOOT || action == ActionId::SHOOT_LONG) && res.success) {
                Logger::logScoreboard(match);
            }
            
            // Pausa para que no sea un bloque de texto instantáneo.
            std::this_thread::sleep_for(std::chrono::milliseconds(12));
        }
    }

    if (verbose) {
        Logger::logSummary(match);
    }

    return match;
}

bool SimulationLoop::isFinished(const Match& match) {
    // Corta a los 90 clavados (se puede expandir para agregar alargue/descuento)
    return match.state.minute >= 90;
}

} // namespace mfm