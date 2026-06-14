#include "mfm/DuelResolvers.hpp"
#include "mfm/Weights.hpp"

namespace mfm::resolvers {

ResolutionResult resolveShoot(const Match& match, const Team& attackers, const Team& defenders, ActionId action, const Context& ctx) {
    ResolutionResult res;
    res.new_possession = match.state.possession;
    
    const auto& carrier = attackers.squad[match.state.ball_carrier_idx];
    const auto& gk = defenders.squad[0];

    TeamId def_team = (match.state.possession == TeamId::HOME) ? TeamId::AWAY : TeamId::HOME;

    float exec_mod = getFatigueModifier(match, match.state.possession, carrier.line);
    float gk_exec_mod = getFatigueModifier(match, def_team, gk.line);

    float attack = (carrier.attrs.shooting * Weights::resShootTech() + 
                    carrier.attrs.composure * Weights::resShootComp()) * exec_mod;
    
    if (action == ActionId::SHOOT_LONG) {
        attack *= Weights::resShootLongPenalty(); 
    }

    // 1. ¿Va al arco? Esto depende PURAMENTE del atacante.
    // Un tiro decente tiene muchas chances de ir entre los 3 palos.
    float p_target = std::clamp(attack * 0.85f, 20.0f, 95.0f); 

    if (RNG::random() * 100.0f < p_target) {
        
        // 2. Va al arco. Acá chocan los atributos directamente (Opposed Check).
        float defense = (gk.attrs.reflexes_gk * Weights::resGkRef() + 
                         gk.attrs.positioning_gk * Weights::resGkPos()) * gk_exec_mod;
        
        float duel_advantage = attack - defense;
        float p_goal = Weights::duelBase() + (duel_advantage * Weights::duelScale());
        p_goal = std::clamp(p_goal, 5.0f, 95.0f);
        
        if (RNG::random() * 100.0f < p_goal) {
            res.success = true;
            res.new_zone = ZoneId::MID_C; 
            res.new_possession = def_team;
            res.new_carrier_idx = 6;
            res.description = "¡GOOOOOL! Misil inatajable de " + carrier.name + ".";
        } else {
            res.success = false;
            res.new_zone = ctx.zone; 
            res.new_possession = def_team;
            res.new_carrier_idx = 0; 
            res.description = "¡Tremenda volada de " + gk.name + "! Le ahogó el grito a " + carrier.name + ".";
        }
    } else {
        res.success = false;
        res.new_zone = ZoneId::DEF_C; 
        res.new_possession = def_team;
        res.new_carrier_idx = 0;
        res.description = "Tiro desviado de " + carrier.name + " que se pierde en la tribuna.";
    }

    return res;
}

} // namespace mfm::resolvers