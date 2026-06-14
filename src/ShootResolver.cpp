#include "mfm/DuelResolvers.hpp"
#include "mfm/Config.hpp"

namespace mfm::resolvers {

ResolutionResult resolveShoot(const Match& match, const Team& attackers, const Team& defenders, ActionId action, const Context& ctx) {
    ResolutionResult res;
    const auto& carrier = attackers.squad[match.state.ball_carrier_idx];
    const auto& gk = defenders.squad[0];

    auto& cfg = Config::getInstance();
    float exec_mod = getFatigueModifier(match, match.state.possession, carrier.line);
    float dice = RNG::random() * 100.0f;
    
    float w_tech = cfg.get("RES_SHOOT_TECH", 0.6f);
    float w_comp = cfg.get("RES_SHOOT_COMP", 0.4f);
    float target_chance = (carrier.attrs.shooting * w_tech + carrier.attrs.composure * w_comp) * exec_mod;
    
    if (action == ActionId::SHOOT_LONG) {
        target_chance *= cfg.get("RES_SHOOT_LONG_PENALTY", 0.7f); 
    }

    if (dice < target_chance) {
        float w_gref = cfg.get("RES_GK_REF", 0.6f);
        float w_gpos = cfg.get("RES_GK_POS", 0.4f);
        float save_chance = (gk.attrs.reflexes_gk * w_gref + gk.attrs.positioning_gk * w_gpos);
        float gk_dice = RNG::random() * 100.0f;
        
        if (gk_dice > save_chance) {
            res.success = true;
            res.new_zone = ZoneId::MID_C; 
            res.new_possession = (match.state.possession == TeamId::HOME) ? TeamId::AWAY : TeamId::HOME;
            res.new_carrier_idx = 6;
            res.description = "¡GOOOOOL! Misil inatajable de " + carrier.name + ".";
        } else {
            res.success = false;
            res.new_zone = ctx.zone; 
            res.new_possession = (match.state.possession == TeamId::HOME) ? TeamId::AWAY : TeamId::HOME;
            res.new_carrier_idx = 0; 
            res.description = "¡Tremenda volada de " + gk.name + "! Le ahogó el grito a " + carrier.name + ".";
        }
    } else {
        res.success = false;
        res.new_zone = ZoneId::DEF_C; 
        res.new_possession = (match.state.possession == TeamId::HOME) ? TeamId::AWAY : TeamId::HOME;
        res.new_carrier_idx = 0;
        res.description = "Tiro desviado de " + carrier.name + " que se pierde en la tribuna.";
    }

    return res;
}

} // namespace mfm::resolvers