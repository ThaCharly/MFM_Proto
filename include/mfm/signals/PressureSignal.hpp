#pragma once
#include "../ActionDist.hpp"
#include "../ContextExtractor.hpp"
#include "../Weights.hpp"

namespace mfm {

// Señal 4 de 7: Presión táctica efectiva.
// Pregunta: ¿Cuánto espacio real tiene el jugador para pensar?
// A mayor presión, el jugador simplifica o aguanta. Jamás busca el pase difícil.
// ctx.pressure ya incorpora press_style y defensive_line del rival (ContextExtractor).
struct PressureSignal {
    static void apply(ActionDist& dist, const Context& ctx) {
        switch (ctx.pressure) {
            case PressureLevel::EXTREME:
                dist[A(ActionId::PASS_SAFE)]  *= Weights::pressExtPassSafe();
                dist[A(ActionId::HOLD)]       *= Weights::pressExtHold();
                dist[A(ActionId::PASS_RISKY)] *= Weights::pressExtPassRisky();
                dist[A(ActionId::DRIBBLE)]    *= Weights::pressExtDribble();
                dist[A(ActionId::SHOOT)]      *= Weights::pressExtShoot(); // el tiro apresurado existe pero es malo
                break;
            case PressureLevel::HIGH:
                dist[A(ActionId::PASS_SAFE)]  *= Weights::pressHighPassSafe();
                dist[A(ActionId::PASS_RISKY)] *= Weights::pressHighPassRisky();
                break;
            case PressureLevel::LOW:
            case PressureLevel::MEDIUM:
                break; // distribución base correcta, no tocar
        }
    }
};

} // namespace mfm