#pragma once
#include "Team.hpp"
#include "Match.hpp"

namespace mfm {

// El orquestador principal. Conecta las Fases 3, 4 y 5 secuencialmente.
class SimulationLoop {
public:
    // Si 'verbose' es true, imprime en consola y hace pausas (Real-Time).
    // Si 'verbose' es false, corre a máxima velocidad en memoria (Batch).
    static Match run(const Team& home, const Team& away, uint32_t seed, bool verbose);

private:
    static bool isFinished(const Match& match);
};

} // namespace mfm