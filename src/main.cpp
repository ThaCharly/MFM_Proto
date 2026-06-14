#include "mfm/Config.hpp"
#include "mfm/SimulationLoop.hpp"
#include "mfm/Logger.hpp"
#include "mfm/TeamBuilder.hpp"
#include <iostream>
#include <filesystem>
#include <chrono>

void runRealTime() {
    std::filesystem::path logPath = std::filesystem::current_path() / "partido.txt";
    mfm::Logger::init(logPath.string());
    
    auto home = mfm::TeamBuilder::createNacional();
    auto away = mfm::TeamBuilder::createPenarol();
    
    mfm::SimulationLoop::run(home, away, 42, true);
    
    mfm::Logger::close();
}

void runBatchMode(int iterations) {
    std::cout << "\nSimulando " << iterations << " partidos (Modo Batch silencioso)...\n";
    auto home = mfm::TeamBuilder::createNacional();
    auto away = mfm::TeamBuilder::createPenarol();
    
    int home_wins = 0, away_wins = 0, draws = 0;
    long total_goals = 0;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        mfm::Match m = mfm::SimulationLoop::run(home, away, 1337 + i, false);
        
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
    std::filesystem::path cfgPath = std::filesystem::current_path() / "weights.cfg";
    mfm::Config::getInstance().load(cfgPath.string());

    int mode = 1;
    std::cout << "1 -> Partido en Tiempo Real\n2 -> Simulación Batch (2000 partidos)\nElegí [1-2]: ";
    std::cin >> mode;

    if (mode == 1) runRealTime();
    else runBatchMode(2000);

    return 0;
}