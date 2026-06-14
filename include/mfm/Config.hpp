#pragma once
#include <string>
#include <unordered_map>

namespace mfm {

// Singleton que actúa como memoria de solo lectura para los pesos del motor.
// Separa estrictamente la matemática hardcodeada de la configuración dinámica.
class Config {
public:
    // Punto de acceso global y único a la instancia en memoria.
    static Config& getInstance();

    // Blindaje de arquitectura: Prohibimos la copia y asignación para evitar 
    // duplicación de datos o fugas de memoria por error humano.
    Config(const Config&) = delete;
    void operator=(const Config&) = delete;

    // Lee el archivo de texto plano y carga los pares clave-valor en la RAM.
    void load(const std::string& filepath);

    // Retorna el valor asociado a la clave. 
    // Si la clave no existe en el archivo o se escribió mal, inyecta el defaultValue de forma segura.
    float get(const std::string& key, float defaultValue) const;

private:
    // Constructor privado para forzar el uso de getInstance().
    Config() = default;

    // Tabla Hash interna. Garantiza tiempos de acceso O(1) promedio durante la simulación.
    std::unordered_map<std::string, float> m_weights;
};

} // namespace mfm