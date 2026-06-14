#include "mfm/StateUpdater.hpp"
#include "mfm/StatsTracker.hpp"
#include "mfm/Weights.hpp"
#include <algorithm>

namespace mfm {

void StateUpdater::applyResolution(Match& match, ActionId action, const ResolutionResult& res) {
    TeamId original_possession = match.state.possession;
    TeamId rival_team = (original_possession == TeamId::HOME) ? TeamId::AWAY : TeamId::HOME;

    // 1. REGISTRO ESTADÍSTICO SEGÚN LA ACCIÓN Y EL RESULTADO
    switch (action) {
        case ActionId::PASS_SAFE:
        case ActionId::PASS_RISKY:
        case ActionId::LONG_BALL:
        case ActionId::CROSS:
            StatsTracker::recordPassAttempt(match.stats, original_possession);
            if (res.success) {
                StatsTracker::recordPassSuccess(match.stats, original_possession);
            } else {
                StatsTracker::recordInterception(match.stats, rival_team);
            }
            break;

        case ActionId::DRIBBLE:
        case ActionId::HOLD:
            if (!res.success) {
                StatsTracker::recordTackle(match.stats, rival_team);
            }
            break;

        case ActionId::SHOOT:
        case ActionId::SHOOT_LONG:
            if (res.success) {
                // Fue gol
                StatsTracker::recordShotOnTarget(match.stats, original_possession);
                StatsTracker::recordGoal(match.stats, original_possession);
            } else {
                // En ShootResolver: Atajada mantiene la zona, errar la manda a DEF_C (saque de arco)
                if (res.new_zone != ZoneId::DEF_C) {
                    StatsTracker::recordShotOnTarget(match.stats, original_possession);
                    StatsTracker::recordSave(match.stats, rival_team); 
                } else {
                    StatsTracker::recordShotOffTarget(match.stats, original_possession);
                }
            }
            break;
        default: break;
    }

    // 2. MUTACIÓN DEL ESTADO MACRO (Lo que dictaminó la matemática)
    match.state.ball_zone = res.new_zone;
    match.state.possession = res.new_possession;
    match.state.ball_carrier_idx = res.new_carrier_idx;

    // 3. ACTUALIZACIÓN DE VARIABLES EMERGENTES (Momentum, Tensión)
    if (res.success && action <= ActionId::CROSS) {
        match.state.consecutive_passes++;
        match.state.pressure_index = std::clamp(match.state.pressure_index + Weights::pressIncSuccess(), 0.0f, 1.0f);
        match.state.momentum += (original_possession == TeamId::HOME) ? Weights::momentumIncSuccess() : -Weights::momentumIncSuccess();
    } else if (res.new_possession != original_possession) {
        // Pérdida de pelota: se resetea la cadena
        match.state.consecutive_passes = 0;
        match.state.pressure_index = Weights::pressResetLoss(); 
        
        // Si no fue por un gol en contra, marca transición
        if (action != ActionId::SHOOT && action != ActionId::SHOOT_LONG) {
            match.state.phase = GamePhase::TRANSITION_ATK;
        }
    }

    if (res.success && (action == ActionId::SHOOT || action == ActionId::SHOOT_LONG)) {
        // Golazo: se resetea todo a saque del medio
        match.state.consecutive_passes = 0;
        match.state.pressure_index = Weights::pressResetGoal();
        match.state.momentum = (original_possession == TeamId::HOME) ? Weights::momentumResetGoal() : -Weights::momentumResetGoal();
        match.state.phase = GamePhase::OPEN_PLAY;
    }

    match.state.momentum = std::clamp(match.state.momentum, -1.0f, 1.0f);

    // 4. TIEMPO EMERGENTE
    // Un tiro es rapidísimo. Retener la pelota lleva tiempo. 
    float dt = Weights::timeBase(); // Base en segundos reales por acción
    if (action == ActionId::HOLD) dt = Weights::timeHold();
    else if (action == ActionId::PASS_SAFE) dt = Weights::timePassSafe();
    else if (action == ActionId::SHOOT || action == ActionId::SHOOT_LONG) dt = Weights::timeShoot();

    advanceTime(match, dt);
    accumulateFatigue(match, dt);
}

void StateUpdater::advanceTime(Match& match, float dt_seconds) {
    // Convierte los segundos lógicos de la acción al reloj del partido.
    // Ej: dt = 3.0s -> sumamos 3 al segundo actual.
    match.state.second += static_cast<int>(dt_seconds);
    
    if (match.state.second >= 60) {
        match.state.minute += (match.state.second / 60);
        match.state.second %= 60;
    }
}

void StateUpdater::accumulateFatigue(Match& match, float dt_seconds) {
    // Tasa de fatiga base por segundo
    float base_rate = Weights::fatigueBaseRate();
    float home_rate = base_rate;
    float away_rate = base_rate;

    // TODO: En el SimulationLoop vamos a necesitar inyectar las tácticas acá.
    // Por ahora acumulamos la fatiga base lineal para todas las líneas.
    for (int i = 0; i < 4; ++i) {
        match.state.fatigue_home[i] += home_rate * dt_seconds;
        match.state.fatigue_away[i] += away_rate * dt_seconds;
    }
}

} // namespace mfm