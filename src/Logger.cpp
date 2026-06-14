#include "mfm/Logger.hpp"
#include "mfm/StatsTracker.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

namespace mfm {

std::ofstream Logger::m_file;

void Logger::init(const std::string& filepath) {
    m_file.open(filepath, std::ios::trunc);
    if (!m_file.is_open()) {
        std::cerr << "[WARNING] Logger no pudo abrir/crear: " << filepath << "\n";
        return;
    }
    std::string header = "========================================================\n"
                         "          REGISTRO DEL PARTIDO - MFM ENGINE v0.2        \n"
                         "========================================================\n\n";
    std::cout << header;
    m_file << header;
}

void Logger::logEvent(const Match& match, const ResolutionResult& res) {
    std::string timeStr = formatTime(match.state.minute, match.state.second);
    std::string logLine = timeStr + " | " + res.description + "\n";
    
    std::cout << logLine;
    if (m_file.is_open()) m_file << logLine;
}

void Logger::logScoreboard(const Match& match) {
    std::ostringstream oss;
    oss << "--------------------------------------------------------\n"
        << " [MARCADOR] Local " << match.stats.goals_home 
        << " - " << match.stats.goals_away << " Visitante\n"
        << "--------------------------------------------------------\n";
    
    std::cout << oss.str();
    if (m_file.is_open()) m_file << oss.str();
}

void Logger::logSummary(const Match& match) {
    std::string summary = StatsTracker::summarize(match.stats);
    std::cout << summary;
    if (m_file.is_open()) m_file << summary;
}

void Logger::close() {
    if (m_file.is_open()) m_file.close();
}

std::string Logger::formatTime(int min, int sec) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << min << ":" 
        << std::setfill('0') << std::setw(2) << sec;
    return oss.str();
}

} // namespace mfm