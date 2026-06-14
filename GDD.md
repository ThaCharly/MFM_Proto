Envíame TODOS los archivos de la Fase x con BUENOS comentarios. Nada de ocupar espacio con ellos, que sean explicativos, fuertes y concisos.






🧱 Fase 1: Definición de Estructuras Atómicas (Data-Only)

Objetivo: Crear los contenedores de datos puros. Cero lógica, solo structs, enums y la abstracción del azar.

    Types.hpp: Enums globales del sistema (Zonas, Clases de Zona, Fases de Juego).

    Random.hpp: Clase estática RNG con semilla única para garantizar el determinismo total.

    Player.hpp: Perfil y matriz de 19 atributos del futbolista.

    Tactics.hpp: Estilos de juego, pressing, altura de línea y amplitudes.

    Team.hpp: Estructura que junta el nombre, la formación, la táctica y el vector de 11 jugadores.

    MatchStats.hpp: El acumulador histórico inmutable del partido (goles, pases, tiros, atajadas).

    GameState.hpp: El estado dinámico y volátil del partido en el instante t (tiempo, posesión, portador, zona, fatigas).

⚙️ Fase 2: subsistema de Configuración (I/O Dinámico)

Objetivo: Separar las constantes matemáticas del código binario.

    Config.hpp / Config.cpp: Singleton encargado de parsear el archivo externo weights.cfg. Centraliza la lectura de probabilidades base y multiplicadores.

🧠 Fase 3: El Cerebro Estocástico (Inferencia y Muestreo)

Objetivo: Determinar qué quiere hacer el jugador con la pelota.

    ActionTypes.hpp: Enum con el catálogo de acciones posibles (PASS_SAFE, SHOOT, etc.).

    ContextExtractor.hpp / ContextExtractor.cpp: Lee el GameState y el Team para escupir un Context simplificado (ej: nivel de presión efectiva, líneas de pase disponibles).

    InferenceEngine.hpp / InferenceEngine.cpp: Cruza el Context y el PlayerProfile con los pesos de Config para armar la función de distribución de probabilidad (∑P=1.0).

    Sampler.hpp / Sampler.cpp: Consume esa distribución y le pide un número al RNG para dictaminar la acción final.

⚔️ Fase 4: Los Micro-Resolución de Duelos (Física y Atributos)

Objetivo: Resolver si la acción elegida tiene éxito o falla, aislando las matemáticas.

    DuelResolvers.hpp: Interfaz o funciones atómicas para separar la lógica de ejecución.

        PassResolver.cpp: Ecuación lineal limpia de Pase vs Intercepción/Posicionamiento.

        DribbleResolver.cpp: Ecuación de Gambeta/Velocidad vs Entrada.

        ShootResolver.cpp: Tiro contra Reflejos/Posicionamiento del golero.

x🔄 Fase 5: El Núcleo del Estado y actualización (State Machine)

Objetivo: Aplicar las consecuencias del duelo al partido.

    StateUpdater.hpp / StateUpdater.cpp: Modifica el GameState según el resultado (mueve la zona del balón, cambia posesión, acumula fatiga y avanza el reloj con un dt realista).

    StatsTracker.hpp / StatsTracker.cpp: Registra los eventos exitosos o fallidos dentro del MatchStats del partido.

📝 Fase 6: Orquestación, Registro y Consola (Bucle Principal)

Objetivo: Correr el partido y persistir la información.

    Logger.hpp / Logger.cpp: Formatea el texto de forma prolija para la pantalla y el archivo físico partido.txt.

    SimulationLoop.hpp / SimulationLoop.cpp: El director de orquesta que corre el bucle while(!isFinished) llamando secuencialmente a las Fases 3, 4, 5 y 6.

    main.cpp: Punto de entrada. Inicializa el RNG, el Config, define a mano los dos Team (Nacional y Peñarol) con sus variables tácticas, y gatilla la simulación en Modo Tiempo Real o Modo Batch.
