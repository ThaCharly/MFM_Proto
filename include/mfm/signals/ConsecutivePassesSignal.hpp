#pragma once
#include "../ActionDist.hpp"
#include <cstdint>

namespace mfm {

// Bonus signal: Pases encadenados consecutivos.
// Pregunta: ¿El equipo viene circulando y buscando el hueco?
// A más pases, más probable que el siguiente sea el que rompe líneas.
// Simula el build-up real: circulás en corto hasta encontrar la grieta.
struct ConsecutivePassesSignal {
    static void apply(ActionDist& dist, uint8_t consecutive) {
        if (consecutive >= 5) {
            // El equipo tiene ritmo y busca la puñalada
            dist[A(ActionId::PASS_RISKY)] *= 1.4f;
            dist[A(ActionId::SHOOT)]      *= 1.3f;
            dist[A(ActionId::DRIBBLE)]    *= 1.2f;
            dist[A(ActionId::PASS_SAFE)]  *= 0.8f;
        } else if (consecutive >= 3) {
            // Empieza a abrirse el espacio, suave incremento de riesgo
            dist[A(ActionId::PASS_RISKY)] *= 1.15f;
        }
        // 0-2 pases: equipo recién arranca, no modificar
    }
};

} // namespace mfm