#pragma once
#include "../ActionDist.hpp"
#include "../Player.hpp"
#include "../Weights.hpp"

namespace mfm {

// Señal 7 de 7: Perfil de atributos del portador.
// Pregunta: ¿Cómo percibe el mundo este jugador en particular?
// Un jugador con vision=90 VE el pase arriesgado. Uno con vision=40, no.
// Separa el "qué intenta" (infer) del "qué tan bien lo hace" (resolve).
//
// Fórmula de bonus: (stat - 50) / 100.0f → rango [-0.5, +0.5]
// Multiplicador final: (1.0 + bonus * intensidad)
struct AttributeSignal {
    static void apply(ActionDist& dist, const PlayerProfile& carrier) {
        const auto& a = carrier.attrs;

        // Vision: el jugador ve (o no ve) las líneas de pase difíciles
        const float vision_b = (a.vision - 50) / 100.0f;
        dist[A(ActionId::PASS_RISKY)] *= (1.0f + vision_b * Weights::attrVisionMult());

        // Dribbling: la confianza en el regate es proporcional a la habilidad
        const float drib_b = (a.dribbling - 50) / 100.0f;
        dist[A(ActionId::DRIBBLE)] *= (1.0f + drib_b * Weights::attrDribbleMult());

        // Composure: los calmos no rematan a lo loco bajo presión
        const float comp_b = (a.composure - 50) / 100.0f;
        dist[A(ActionId::SHOOT)] *= (1.0f - comp_b * Weights::attrComposureMult());

        // Shooting: los goleadores buscan el tiro, los mediocres lo evitan
        const float shoot_b = (a.shooting - 50) / 100.0f;
        dist[A(ActionId::SHOOT)]      *= (1.0f + shoot_b * Weights::attrShootMult());
        dist[A(ActionId::SHOOT_LONG)] *= (1.0f + shoot_b * Weights::attrShootLongMult());

        // Strength: los físicos retienen más, los débiles liberan rápido
        const float str_b = (a.strength - 50) / 100.0f;
        dist[A(ActionId::HOLD)] *= (1.0f + str_b * Weights::attrStrengthMult());
    }
};

} // namespace mfm