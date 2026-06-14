#pragma once
#include "Player.hpp"
#include "Tactics.hpp"
#include <vector>
#include <string>

namespace mfm {

// Contenedor estático del equipo. Se carga al inicio y no se muta durante el partido.
struct Team {
    std::string name;
    FormationId formation;
    TacticsProfile tactics;
    std::vector<PlayerProfile> squad; // Se asume longitud estricta de 11 jugadores.
};

} // namespace mfm