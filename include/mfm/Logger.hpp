#pragma once
#include "Match.hpp"
#include "DuelResolvers.hpp"
#include <string>
#include <fstream>

namespace mfm {

// Maneja la salida a consola y al archivo de texto de forma centralizada.
// En modo Batch, se puede mutear para que no reviente la CPU con I/O de disco.
class Logger {
public:
    static void init(const std::string& filepath);
    static void logEvent(const Match& match, const ResolutionResult& res);
    static void logScoreboard(const Match& match);
    static void logSummary(const Match& match);
    static void close();

private:
    static std::string formatTime(int min, int sec);
    static std::ofstream m_file;
};

} // namespace mfm