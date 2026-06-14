#pragma once
#include "../ActionDist.hpp"
#include "../ContextExtractor.hpp"

namespace mfm {

// Señal 4 de 7: Presión táctica efectiva.
// Pregunta: ¿Cuánto espacio real tiene el jugador para pensar?
// A mayor presión, el jugador simplifica o aguanta. Jamás busca el pase difícil.
// ctx.pressure ya incorpora press_style y defensive_line del rival (ContextExtractor).
struct PressureSignal {
    static void apply(ActionDist& dist, const Context& ctx) {
        switch (ctx.pressure) {
            case PressureLevel::EXTREME:
                dist[A(ActionId::PASS_SAFE)]  *= 1.4f;
                dist[A(ActionId::HOLD)]       *= 1.3f;
                dist[A(ActionId::PASS_RISKY)] *= 0.4f;
                dist[A(ActionId::DRIBBLE)]    *= 0.5f;
                dist[A(ActionId::SHOOT)]      *= 0.7f; // el tiro apresurado existe pero es malo
                break;
            case PressureLevel::HIGH:
                dist[A(ActionId::PASS_SAFE)]  *= 1.2f;
                dist[A(ActionId::PASS_RISKY)] *= 0.7f;
                break;
            case PressureLevel::LOW:
            case PressureLevel::MEDIUM:
                break; // distribución base correcta, no tocar
        }
    }
};

} // namespace mfm