#include "mfm/ContextExtractor.hpp"

namespace mfm {

Context ContextExtractor::extract(
    const Match& match,
    const Team& home,
    const Team& away
) {
    Context ctx;

    const auto& state = match.state;
    const auto& stats = match.stats;

    ctx.zone = state.ball_zone;

    // 1. Traducción espacial
    if (ctx.zone <= ZoneId::DEF_R)
        ctx.zone_class = ZoneClass::DEFENSIVE;
    else if (ctx.zone <= ZoneId::MID_R)
        ctx.zone_class = ZoneClass::TRANSITION;
    else if (ctx.zone <= ZoneId::ATK_R)
        ctx.zone_class = ZoneClass::OFFENSIVE;
    else
        ctx.zone_class = ZoneClass::DANGER_AREA;

    // 2. Presión Táctica Efectiva
    const auto& rival_tactics =
        (state.possession == TeamId::HOME)
            ? away.tactics
            : home.tactics;

    float tactical_boost = 0.0f;

    if (rival_tactics.press_style == PressStyle::HIGH_PRESS)
        tactical_boost = 0.15f;
    else if (rival_tactics.press_style == PressStyle::GEGENPRESSING)
        tactical_boost = 0.25f;

    if (rival_tactics.defensive_line > 0.6f &&
        (ctx.zone_class == ZoneClass::DEFENSIVE ||
         ctx.zone_class == ZoneClass::TRANSITION))
    {
        tactical_boost += 0.15f;
    }

    float effective_pressure = state.pressure_index + tactical_boost;

    if (effective_pressure > 0.75f)
        ctx.pressure = PressureLevel::EXTREME;
    else if (effective_pressure > 0.50f)
        ctx.pressure = PressureLevel::HIGH;
    else if (effective_pressure > 0.25f)
        ctx.pressure = PressureLevel::MEDIUM;
    else
        ctx.pressure = PressureLevel::LOW;

    ctx.space_available = (effective_pressure < 0.4f);

    // 3. Momento y Score
    if (state.minute > 85)
        ctx.moment = MatchMoment::FINAL_MINUTES;
    else if (state.minute > 60)
        ctx.moment = MatchMoment::LATE;
    else if (state.minute > 25)
        ctx.moment = MatchMoment::MID;
    else
        ctx.moment = MatchMoment::EARLY;

    int diff = static_cast<int>(stats.goals_home)
             - static_cast<int>(stats.goals_away);

    if (state.possession == TeamId::AWAY)
        diff = -diff;

    if (diff > 1)
        ctx.score_context = ScoreContext::WINNING_COMFORTABLE;
    else if (diff == 1)
        ctx.score_context = ScoreContext::WINNING_TIGHT;
    else if (diff == 0)
        ctx.score_context = ScoreContext::LEVEL;
    else if (diff == -1)
        ctx.score_context = ScoreContext::LOSING_TIGHT;
    else
        ctx.score_context = ScoreContext::LOSING_COMFORTABLE;

    // 4. Estados transitorios
    ctx.on_transition = (state.phase == GamePhase::TRANSITION_ATK);
    ctx.carrier_fatigue = FatigueLevel::FRESH;
    ctx.passing_lanes = (ctx.pressure == PressureLevel::EXTREME) ? 1 : 3;

    return ctx;
}

} // namespace mfm