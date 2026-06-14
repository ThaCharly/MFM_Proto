#pragma once
#include "GameState.hpp"
#include "MatchStats.hpp"
#include "Team.hpp"

namespace mfm {

struct Match {
    GameState state;
    MatchStats stats;
};


} // namespace mfm