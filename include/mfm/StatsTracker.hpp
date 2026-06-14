#pragma once
#include "MatchStats.hpp"
#include "ActionTypes.hpp"
#include "Types.hpp"
#include <string>

namespace mfm {

// Contenedor estático puro. Incrementa los contadores del MatchStats.
class StatsTracker {
public:
    static void recordPassAttempt(MatchStats& stats, TeamId team);
    static void recordPassSuccess(MatchStats& stats, TeamId team);
    
    static void recordShotAttempt(MatchStats& stats, TeamId team);
    static void recordShotOnTarget(MatchStats& stats, TeamId team);
    static void recordShotOffTarget(MatchStats& stats, TeamId team);
    
    static void recordGoal(MatchStats& stats, TeamId team);
    
    // Se le anota al equipo que defiende (team_defending)
    static void recordSave(MatchStats& stats, TeamId team_defending);
    static void recordInterception(MatchStats& stats, TeamId team_defending);
    static void recordTackle(MatchStats& stats, TeamId team_defending);

    // Devuelve un string prolijo con el resumen de stats para la consola
    static std::string summarize(const MatchStats& stats);
};

} // namespace mfm