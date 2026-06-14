#pragma once
#include "Team.hpp"

namespace mfm {

// Clase dedicada puramente a instanciar los datos de los equipos.
// Aleja el ruido y las miles de líneas del flujo principal del programa.
class TeamBuilder {
public:
    static Team createNacional();
    static Team createPenarol();
};

} // namespace mfm