#include "mfm/DuelResolvers.hpp"
#include "mfm/Config.hpp"

namespace mfm::resolvers {

ResolutionResult resolvePass(const Match& match, const Team& attackers, const Team& defenders, ActionId action, const Context& ctx) {
    ResolutionResult res;
    res.new_possession = match.state.possession; 
    
    const auto& carrier = attackers.squad[match.state.ball_carrier_idx];
    size_t def_idx = pickDefenderIndex(ctx.zone_class);
    const auto& defender = defenders.squad[def_idx];

    auto& cfg = Config::getInstance();
    float exec_mod = getFatigueModifier(match, match.state.possession, carrier.line);
    float dice = RNG::random() * 100.0f;
    float p_success = 0.0f;

    if (action == ActionId::PASS_SAFE) {
        float w_tech = cfg.get("RES_PASS_SAFE_TECH", 0.7f);
        float w_comp = cfg.get("RES_PASS_SAFE_COMP", 0.3f);
        float w_def  = cfg.get("RES_PASS_SAFE_DEF_POS", 0.2f);

        p_success = (carrier.attrs.passing * w_tech + carrier.attrs.composure * w_comp) * exec_mod;
        p_success -= (defender.attrs.positioning * w_def);
        
        res.success = (dice < std::clamp(p_success, 15.0f, 95.0f));
        
        if (res.success) {
            int z = static_cast<int>(ctx.zone);
            res.new_zone = (z < static_cast<int>(ZoneId::ATK_L)) ? static_cast<ZoneId>(z + 3) : ctx.zone;
            res.new_carrier_idx = (match.state.ball_carrier_idx + 1 + RNG::range(0, 2)) % 11;
            if (res.new_carrier_idx == 0) res.new_carrier_idx = 5; 
            res.description = carrier.name + " toca en corto asegurando la guinda.";
        } else {
            res.new_possession = (match.state.possession == TeamId::HOME) ? TeamId::AWAY : TeamId::HOME;
            res.new_carrier_idx = def_idx;
            res.description = carrier.name + " erra un pase de rutina. Recupera " + defender.name + ".";
        }
    } 
    else { 
        float w_tech = cfg.get("RES_PASS_RISK_TECH", 0.4f);
        float w_vis  = cfg.get("RES_PASS_RISK_VIS", 0.4f);
        float w_comp = cfg.get("RES_PASS_RISK_COMP", 0.2f);
        float w_dant = cfg.get("RES_PASS_RISK_DEF_ANT", 0.4f);
        float w_dpos = cfg.get("RES_PASS_RISK_DEF_POS", 0.3f);

        p_success = (carrier.attrs.passing * w_tech + carrier.attrs.vision * w_vis + carrier.attrs.composure * w_comp) * exec_mod;
        p_success -= (defender.attrs.anticipation * w_dant + defender.attrs.positioning * w_dpos);
        
        res.success = (dice < std::clamp(p_success, 5.0f, 85.0f));
        
        if (res.success) {
            res.new_zone = ZoneId::BOX_C; 
            res.new_carrier_idx = RNG::range(8, 10); 
            res.description = carrier.name + " mete una puñalada barbara rompiendo líneas.";
        } else {
            res.new_possession = (match.state.possession == TeamId::HOME) ? TeamId::AWAY : TeamId::HOME;
            res.new_carrier_idx = def_idx;
            res.description = "Intento filtrado de " + carrier.name + " que " + defender.name + " lee perfecto y corta.";
        }
    }

    return res;
}

} // namespace mfm::resolvers