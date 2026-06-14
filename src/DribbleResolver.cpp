#include "mfm/DuelResolvers.hpp"
#include "mfm/Config.hpp"

namespace mfm::resolvers {

ResolutionResult resolveDribble(const Match& match, const Team& attackers, const Team& defenders, ActionId action, const Context& ctx) {
    ResolutionResult res;
    const auto& carrier = attackers.squad[match.state.ball_carrier_idx];
    size_t def_idx = pickDefenderIndex(ctx.zone_class);
    const auto& defender = defenders.squad[def_idx];

    auto& cfg = Config::getInstance();
    float exec_mod = getFatigueModifier(match, match.state.possession, carrier.line);
    float dice = RNG::random() * 100.0f;
    float p_success = 0.0f;

    if (action == ActionId::DRIBBLE) {
        float w_tech   = cfg.get("RES_DRIBBLE_TECH", 0.6f);
        float w_pace   = cfg.get("RES_DRIBBLE_PACE", 0.4f);
        float w_dtack  = cfg.get("RES_DRIBBLE_DEF_TACK", 0.6f);
        float w_dpace  = cfg.get("RES_DRIBBLE_DEF_PACE", 0.4f);

        p_success = (carrier.attrs.dribbling * w_tech + carrier.attrs.pace * w_pace) * exec_mod;
        p_success -= (defender.attrs.tackling * w_dtack + defender.attrs.pace * w_dpace);
        
        res.success = (dice < std::clamp(p_success, 10.0f, 90.0f));
        
        if (res.success) {
            int z = static_cast<int>(ctx.zone);
            res.new_zone = (z < static_cast<int>(ZoneId::BOX_L)) ? static_cast<ZoneId>(z + 1) : ctx.zone;
            res.new_possession = match.state.possession;
            res.new_carrier_idx = match.state.ball_carrier_idx;
            res.description = carrier.name + " apila rivales con una finta limpia.";
        } else {
            res.new_possession = (match.state.possession == TeamId::HOME) ? TeamId::AWAY : TeamId::HOME;
            res.new_carrier_idx = def_idx;
            res.description = defender.name + " va firme abajo y le come la pelota a " + carrier.name + ".";
        }
    } 
    else if (action == ActionId::HOLD) {
        float w_str   = cfg.get("RES_HOLD_STR", 0.7f);
        float w_comp  = cfg.get("RES_HOLD_COMP", 0.3f);
        float w_dstr  = cfg.get("RES_HOLD_DEF_STR", 0.5f);
        float w_dmark = cfg.get("RES_HOLD_DEF_MARK", 0.3f);

        p_success = (carrier.attrs.strength * w_str + carrier.attrs.composure * w_comp) * exec_mod;
        p_success -= (defender.attrs.strength * w_dstr + defender.attrs.marking * w_dmark);
        
        res.success = (dice < std::clamp(p_success, 20.0f, 95.0f));
        
        if (res.success) {
            res.new_zone = ctx.zone;
            res.new_possession = match.state.possession;
            res.new_carrier_idx = match.state.ball_carrier_idx;
            res.description = carrier.name + " pone el cuerpo de espaldas y esconde el esférico.";
        } else {
            res.new_possession = (match.state.possession == TeamId::HOME) ? TeamId::AWAY : TeamId::HOME;
            res.new_carrier_idx = def_idx;
            res.description = defender.name + " anticipa con potencia y lo desplaza a " + carrier.name + ".";
        }
    }

    return res;
}

} // namespace mfm::resolvers