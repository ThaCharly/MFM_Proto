#include "mfm/DuelResolvers.hpp"
#include "mfm/Weights.hpp"

namespace mfm::resolvers {

ResolutionResult resolvePass(
    const Match& match,
    const Team& attackers,
    const Team& defenders,
    ActionId action,
    const Context& ctx
) {
    ResolutionResult res;

    res.new_possession = match.state.possession;

    const auto& carrier =
        attackers.squad[match.state.ball_carrier_idx];

    size_t def_idx =
        pickDefenderIndex(ctx.zone_class);

    const auto& defender =
        defenders.squad[def_idx];

    float exec_mod =
        getFatigueModifier(
            match,
            match.state.possession,
            carrier.line
        );

    float attack = 0.0f;
    float defense = 0.0f;
    float p_success = 0.0f;

    if (action == ActionId::PASS_SAFE)
    {
        attack =
            carrier.attrs.passing *
                Weights::resPassSafeTech()
            +
            carrier.attrs.composure *
                Weights::resPassSafeComp();

        defense =
            defender.attrs.positioning *
                Weights::resPassSafeDefPos();

        attack *= exec_mod;

        float duel_advantage = attack - defense;

        p_success =
            Weights::duelBase() +
            (duel_advantage * Weights::duelScale());

        p_success =
            std::clamp(
                p_success,
                15.0f,
                95.0f
            );

        res.success =
            RNG::random() * 100.0f < p_success;

        if (res.success)
        {
            int z =
                static_cast<int>(ctx.zone);

            res.new_zone =
                (z < static_cast<int>(ZoneId::ATK_L))
                    ? static_cast<ZoneId>(z + 3)
                    : ctx.zone;

            res.new_carrier_idx =
                (match.state.ball_carrier_idx +
                 1 +
                 RNG::range(0, 2))
                % 11;

            if (res.new_carrier_idx == 0)
                res.new_carrier_idx = 5;

            res.description =
                carrier.name +
                " toca en corto asegurando la guinda.";
        }
        else
        {
            res.new_possession =
                (match.state.possession ==
                 TeamId::HOME)
                    ? TeamId::AWAY
                    : TeamId::HOME;

            res.new_carrier_idx =
                def_idx;

            res.description =
                carrier.name +
                " erra un pase de rutina. Recupera " +
                defender.name + ".";
        }
    }
    else
    {
        attack =
            carrier.attrs.passing *
                Weights::resPassRiskTech()
            +
            carrier.attrs.vision *
                Weights::resPassRiskVis()
            +
            carrier.attrs.composure *
                Weights::resPassRiskComp();

        defense =
            defender.attrs.anticipation *
                Weights::resPassRiskDefAnt()
            +
            defender.attrs.positioning *
                Weights::resPassRiskDefPos();

        attack *= exec_mod;

        float duel_advantage = attack - defense;

        p_success =
            Weights::duelBase() +
            (duel_advantage * Weights::duelScale());

        p_success =
            std::clamp(
                p_success,
                5.0f,
                85.0f
            );

        res.success =
            RNG::random() * 100.0f < p_success;

        if (res.success)
        {
            res.new_zone =
                ZoneId::BOX_C;

            res.new_carrier_idx =
                RNG::range(8, 10);

            res.description =
                carrier.name +
                " mete una puñalada bárbara rompiendo líneas.";
        }
        else
        {
            res.new_possession =
                (match.state.possession ==
                 TeamId::HOME)
                    ? TeamId::AWAY
                    : TeamId::HOME;

            res.new_carrier_idx =
                def_idx;

            res.description =
                "Intento filtrado de " +
                carrier.name +
                " que " +
                defender.name +
                " lee perfecto y corta.";
        }
    }

    return res;
}

} // namespace mfm::resolvers