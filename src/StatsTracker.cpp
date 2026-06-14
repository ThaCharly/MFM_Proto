#include "mfm/StatsTracker.hpp"
#include <sstream>

namespace mfm {

void StatsTracker::recordPassAttempt(MatchStats& stats, TeamId team) {
    if (team == TeamId::HOME) stats.passes_attempted_home++;
    else if (team == TeamId::AWAY) stats.passes_attempted_away++;
}

void StatsTracker::recordPassSuccess(MatchStats& stats, TeamId team) {
    if (team == TeamId::HOME) stats.passes_success_home++;
    else if (team == TeamId::AWAY) stats.passes_success_away++;
}

void StatsTracker::recordShotAttempt(MatchStats& stats, TeamId team) {
    // El intento general se infiere sumando a puerta + afuera en el summarize
}

void StatsTracker::recordShotOnTarget(MatchStats& stats, TeamId team) {
    if (team == TeamId::HOME) stats.shots_on_target_home++;
    else if (team == TeamId::AWAY) stats.shots_on_target_away++;
}

void StatsTracker::recordShotOffTarget(MatchStats& stats, TeamId team) {
    if (team == TeamId::HOME) stats.shots_off_target_home++;
    else if (team == TeamId::AWAY) stats.shots_off_target_away++;
}

void StatsTracker::recordGoal(MatchStats& stats, TeamId team) {
    if (team == TeamId::HOME) stats.goals_home++;
    else if (team == TeamId::AWAY) stats.goals_away++;
}

void StatsTracker::recordSave(MatchStats& stats, TeamId team_defending) {
    if (team_defending == TeamId::HOME) stats.saves_home++;
    else if (team_defending == TeamId::AWAY) stats.saves_away++;
}

void StatsTracker::recordInterception(MatchStats& stats, TeamId team_defending) {
    if (team_defending == TeamId::HOME) stats.interceptions_home++;
    else if (team_defending == TeamId::AWAY) stats.interceptions_away++;
}

void StatsTracker::recordTackle(MatchStats& stats, TeamId team_defending) {
    if (team_defending == TeamId::HOME) stats.tackles_home++;
    else if (team_defending == TeamId::AWAY) stats.tackles_away++;
}

std::string StatsTracker::summarize(const MatchStats& stats) {
    std::ostringstream oss;
    oss << "\n=== ESTADÍSTICAS DEL PARTIDO ===\n";
    oss << "Goles: " << stats.goals_home << " - " << stats.goals_away << "\n";
    oss << "Tiros a puerta: " << stats.shots_on_target_home << " - " << stats.shots_on_target_away << "\n";
    oss << "Tiros afuera: " << stats.shots_off_target_home << " - " << stats.shots_off_target_away << "\n";
    oss << "Atajadas: " << stats.saves_home << " - " << stats.saves_away << "\n";
    oss << "Pases Exitosos: " << stats.passes_success_home << "/" << stats.passes_attempted_home 
        << " - " << stats.passes_success_away << "/" << stats.passes_attempted_away << "\n";
    oss << "Intercepciones: " << stats.interceptions_home << " - " << stats.interceptions_away << "\n";
    oss << "Quites (Tackles): " << stats.tackles_home << " - " << stats.tackles_away << "\n";
    oss << "================================\n";
    return oss.str();
}

} // namespace mfm