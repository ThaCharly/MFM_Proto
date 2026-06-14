#include "mfm/DuelResolvers.hpp"
#include "mfm/Weights.hpp"

namespace mfm::resolvers {

ResolutionResult resolveDribble(const Match& match, const Team& attackers, const Team& defenders, ActionId action, const Context& ctx) {
    ResolutionResult res;
    res.new_possession = match.state.possession;

    const auto& carrier = attackers.squad[match.state.ball_carrier_idx];
    size_t def_idx = pickDefenderIndex(ctx.zone_class);
    const auto& defender = defenders.squad[def_idx];

    TeamId def_team = (match.state.possession == TeamId::HOME) ? TeamId::AWAY : TeamId::HOME;

    float exec_mod = getFatigueModifier(match, match.state.possession, carrier.line);
    float def_exec_mod = getFatigueModifier(match, def_team, defender.line);

    float attack = 0.0f;
    float defense = 0.0f;
    float p_success = 0.0f;

    if (action == ActionId::DRIBBLE) {
        attack = (carrier.attrs.dribbling * Weights::resDribbleTech() + 
                  carrier.attrs.pace * Weights::resDribblePace()) * exec_mod;
                  
        defense = (defender.attrs.tackling * Weights::resDribbleDefTack() + 
                   defender.attrs.pace * Weights::resDribbleDefPace()) * def_exec_mod;
        
        float duel_advantage = attack - defense;
        p_success = Weights::duelBase() + (duel_advantage * Weights::duelScale());
        p_success = std::clamp(p_success, 10.0f, 90.0f);
        
        res.success = (RNG::random() * 100.0f < p_success);
        
        if (res.success) {
            int z = static_cast<int>(ctx.zone);
            res.new_zone = (z < static_cast<int>(ZoneId::BOX_L)) ? static_cast<ZoneId>(z + 1) : ctx.zone;
            res.new_carrier_idx = match.state.ball_carrier_idx;
            res.description = carrier.name + " apila rivales con una finta limpia.";
        } else {
            res.new_possession = def_team;
            res.new_carrier_idx = def_idx;
            res.description = defender.name + " va firme abajo y le come la pelota a " + carrier.name + ".";
        }
    } 
    else if (action == ActionId::HOLD) {
        attack = (carrier.attrs.strength * Weights::resHoldStr() + 
                  carrier.attrs.composure * Weights::resHoldComp()) * exec_mod;
                  
        defense = (defender.attrs.strength * Weights::resHoldDefStr() + 
                   defender.attrs.marking * Weights::resHoldDefMark()) * def_exec_mod;

        float duel_advantage = attack - defense;
        p_success = Weights::duelBase() + (duel_advantage * Weights::duelScale());
        p_success = std::clamp(p_success, 20.0f, 95.0f);
        
        res.success = (RNG::random() * 100.0f < p_success);
        
        if (res.success) {
            res.new_zone = ctx.zone;
            res.new_carrier_idx = match.state.ball_carrier_idx;
            res.description = carrier.name + " pone el cuerpo de espaldas y esconde el esférico.";
        } else {
            res.new_possession = def_team;
            res.new_carrier_idx = def_idx;
            res.description = defender.name + " anticipa con potencia y lo desplaza a " + carrier.name + ".";
        }
    }

    return res;
}

} // namespace mfm::resolvers