#include "../include/mfm/Team.hpp"
#include "../include/mfm/Config.hpp"
#include "../include/mfm/SimulationLoop.hpp"
#include "../include/mfm/Logger.hpp"
#include <iostream>
#include <filesystem>
#include <chrono>

mfm::Team armarNacional() {
    mfm::Team t;
    t.name = "Nacional";
    t.formation = mfm::FormationId::F_433;
    t.tactics = {
        .press_style = mfm::PressStyle::HIGH_PRESS,
        .build_up = mfm::BuildUpStyle::LONG_BALL,
        .atk_transition = mfm::TransitionStyle::FAST_BREAK,
        .def_transition = mfm::TransitionStyle::IMMEDIATE_PRESS,
        .defensive_line = 0.8f,
        .width = 0.4f
    };
    t.squad = {
        {"Mejía [GK]",      mfm::RoleId::GOALKEEPER,           {45, 50, 10, 10, 60, 10, 45, 75, 70, 75, 50, 60, 75, 10, 10, 85, 82, 78, 80}, 0},
        {"Ancheta [DF_R]",  mfm::RoleId::OFFENSIVE_FULLBACK, {65, 68, 70, 50, 65, 72, 60, 70, 70, 68, 80, 85, 72, 74, 68, 10, 10, 10, 10}, 1},
        {"Coates [DF_C]",   mfm::RoleId::CENTER_BACK,          {68, 65, 50, 45, 82, 50, 65, 80, 82, 85, 55, 70, 88, 85, 80, 10, 10, 10, 10}, 1},
        {"Rogel [DF_C]",    mfm::RoleId::CENTER_BACK,          {60, 62, 45, 40, 78, 45, 55, 75, 78, 70, 70, 80, 80, 80, 75, 10, 10, 10, 10}, 1},
        {"Cándido [DF_L]",  mfm::RoleId::DEFENSIVE_FULLBACK, {68, 70, 65, 55, 60, 75, 65, 72, 74, 70, 75, 82, 74, 76, 72, 10, 10, 10, 10}, 1},
        {"Dos Santos[MC_D]",mfm::RoleId::DEFENSIVE_MIDFIELDER, {70, 72, 60, 55, 65, 55, 65, 78, 80, 75, 75, 88, 78, 82, 78, 10, 10, 10, 10}, 2},
        {"Boggio [MC_C]",   mfm::RoleId::BOX_TO_BOX,           {75, 75, 68, 60, 60, 65, 72, 76, 75, 78, 72, 85, 76, 78, 70, 10, 10, 10, 10}, 2},
        {"Diente [MC_A]",   mfm::RoleId::ADVANCED_PLAYMAKER,   {82, 82, 80, 75, 55, 75, 85, 78, 65, 80, 68, 70, 65, 50, 45, 10, 10, 10, 10}, 2},
        {"Lupi [EX_R]",     mfm::RoleId::WINGER,               {68, 72, 82, 68, 55, 78, 65, 70, 60, 68, 88, 84, 65, 45, 40, 10, 10, 10, 10}, 3},
        {"Maxi Gomez[DC]",  mfm::RoleId::TARGET_FORWARD,       {62, 75, 68, 94, 85, 50, 65, 82, 70, 80, 85, 78, 86, 40, 35, 10, 10, 10, 10}, 3},
        {"Martínez [EX_L]", mfm::RoleId::INSIDE_FORWARD,       {72, 76, 80, 80, 80, 65, 70, 78, 65, 78, 78, 75, 82, 45, 40, 10, 10, 10, 10}, 3}
    };
    return t;
}

mfm::Team armarPenarol() {
    mfm::Team t;
    t.name = "Peñarol";
    t.formation = mfm::FormationId::F_442;
    t.tactics = {
        .press_style = mfm::PressStyle::MID_BLOCK,
        .build_up = mfm::BuildUpStyle::PATIENT,
        .atk_transition = mfm::TransitionStyle::CONTROLLED,
        .def_transition = mfm::TransitionStyle::REGROUP,
        .defensive_line = 0.4f,
        .width = 0.5f
    };
    t.squad = {
        {"Aguerre [GK]",    mfm::RoleId::GOALKEEPER,           {50, 55, 10, 10, 60, 10, 40, 72, 68, 70, 55, 60, 70, 10, 10, 84, 80, 75, 78}, 0},
        {"Barboza [DF_R]",  mfm::RoleId::OFFENSIVE_FULLBACK, {70, 72, 75, 60, 55, 75, 68, 70, 68, 72, 82, 84, 65, 70, 65, 10, 10, 10, 10}, 1},
        {"Gularte [DF_C]",  mfm::RoleId::CENTER_BACK,          {62, 65, 48, 45, 85, 45, 55, 78, 80, 75, 60, 75, 86, 82, 78, 10, 10, 10, 10}, 1},
        {"Lemos [DF_C]",    mfm::RoleId::CENTER_BACK,          {65, 68, 50, 40, 80, 50, 60, 76, 78, 74, 65, 78, 82, 80, 75, 10, 10, 10, 10}, 1},
        {"Olivera [DF_L]",  mfm::RoleId::DEFENSIVE_FULLBACK, {65, 68, 60, 45, 65, 68, 60, 74, 72, 70, 78, 80, 75, 78, 72, 10, 10, 10, 10}, 1},
        {"Trindade [MC_D]", mfm::RoleId::DEFENSIVE_MIDFIELDER, {72, 70, 62, 50, 65, 55, 68, 78, 82, 76, 70, 85, 80, 84, 78, 10, 10, 10, 10}, 2},
        {"R. Fernandez",    mfm::RoleId::BOX_TO_BOX,           {74, 75, 70, 65, 60, 68, 75, 78, 74, 75, 78, 86, 72, 76, 68, 10, 10, 10, 10}, 2},
        {"Darias [MC_A]",   mfm::RoleId::ADVANCED_PLAYMAKER,   {80, 80, 78, 72, 55, 75, 82, 75, 65, 78, 72, 72, 65, 55, 50, 10, 10, 10, 10}, 2},
        {"Umpierrez [EX_L]",mfm::RoleId::WINGER,               {72, 76, 80, 68, 55, 76, 70, 72, 60, 70, 85, 80, 65, 45, 40, 10, 10, 10, 10}, 3},
        {"Batista [DC]",    mfm::RoleId::PRESSING_FORWARD,     {65, 72, 70, 80, 78, 55, 65, 80, 75, 78, 78, 82, 78, 50, 45, 10, 10, 10, 10}, 3},
        {"Arezo [EX_R]",    mfm::RoleId::INSIDE_FORWARD,       {70, 75, 82, 75, 65, 72, 68, 75, 65, 74, 86, 78, 70, 45, 40, 10, 10, 10, 10}, 3}
    };
    return t;
}

void runRealTime() {
    std::filesystem::path logPath = std::filesystem::current_path() / "partido.txt";
    mfm::Logger::init(logPath.string());
    
    auto home = armarNacional();
    auto away = armarPenarol();
    
    mfm::SimulationLoop::run(home, away, 42, true); // true = verbose
    
    mfm::Logger::close();
}

void runBatchMode(int iterations) {
    std::cout << "\nSimulando " << iterations << " partidos (Modo Batch silencioso)...\n";
    auto home = armarNacional();
    auto away = armarPenarol();
    
    int home_wins = 0, away_wins = 0, draws = 0;
    long total_goals = 0;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        mfm::Match m = mfm::SimulationLoop::run(home, away, 1337 + i, false); // false = calladito
        
        total_goals += (m.stats.goals_home + m.stats.goals_away);
        if (m.stats.goals_home > m.stats.goals_away) home_wins++;
        else if (m.stats.goals_away > m.stats.goals_home) away_wins++;
        else draws++;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    std::cout << "-> Terminado en " << ms << " ms.\n";
    std::cout << "Local (Nacional) Victorias: " << home_wins << "\n";
    std::cout << "Visitante (Peñarol) Victorias: " << away_wins << "\n";
    std::cout << "Empates: " << draws << "\n";
    std::cout << "Goles totales: " << total_goals << " (Promedio: " << (double)total_goals/iterations << ")\n\n";
}

int main() {
    // 1. Cargar pesos a memoria
    std::filesystem::path cfgPath = std::filesystem::current_path() / "weights.cfg";
    mfm::Config::getInstance().load(cfgPath.string());

    int mode = 1;
    std::cout << "1 -> Partido en Tiempo Real\n2 -> Simulación Batch (2000 partidos)\nElegí [1-2]: ";
    std::cin >> mode;

    if (mode == 1) runRealTime();
    else runBatchMode(2000);

    return 0;
}