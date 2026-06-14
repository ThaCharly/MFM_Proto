#include "mfm/Config.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

namespace mfm {

Config& Config::getInstance() {
    // La variable estática local asegura inicialización "Thread-Safe" en C++11 y superior.
    static Config instance;
    return instance;
}

void Config::load(const std::string& filepath) {
    std::ifstream file(filepath);
    
    // Fallback elegante: Si no encuentra el archivo, no crashea, avisa y usa los hardcodeados.
    if (!file.is_open()) {
        std::cerr << "[MFM-CONFIG] ADVERTENCIA: No se encontró '" << filepath 
                  << "'. El motor usará las matemáticas por defecto.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Filtramos líneas vacías o comentarios estilo script (# o ;)
        if (line.empty() || line[0] == '#' || line[0] == ';') {
            continue;
        }

        auto delimiterPos = line.find('=');
        // Si la línea no tiene un igual, está corrupta. La saltamos.
        if (delimiterPos == std::string::npos) {
            continue; 
        }

        std::string key = line.substr(0, delimiterPos);
        std::string valStr = line.substr(delimiterPos + 1);

        // Función lambda rápida para limpiar mugre (espacios, tabs, saltos de línea ocultos)
        auto trim = [](std::string& s) {
            s.erase(s.find_last_not_of(" \t\r\n") + 1);
            s.erase(0, s.find_first_not_of(" \t\r\n"));
        };
        
        trim(key);
        trim(valStr);

        // Conversión segura de String a Float
        try {
            m_weights[key] = std::stof(valStr);
        } catch (const std::exception& e) {
            std::cerr << "[MFM-CONFIG] ERROR: Valor numérico inválido en cfg para la clave '" 
                      << key << "' -> '" << valStr << "'\n";
        }
    }
    
    std::cout << "[MFM-CONFIG] Archivo de pesos cargado a RAM con éxito. (" 
              << m_weights.size() << " parámetros registrados).\n";
}

float Config::get(const std::string& key, float defaultValue) const {
    auto it = m_weights.find(key);
    if (it != m_weights.end()) {
        return it->second; // Hit: Devuelve el valor del cfg.
    }
    return defaultValue;   // Miss: Devuelve la constante de seguridad.
}

} // namespace mfm