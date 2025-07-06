## 🫧 Sistema de Clima Dinâmico para SA-MP

## O que é?
Sistema que aplica climas diferentes para cada cidade do GTA San Andreas (Los Santos, San Fierro e Las Venturas) com detecção automática da localização do jogador usando áreas dinâmicas.

## Dependencias
### Streamer Plugin v2.9.6 v1.0.0
- Download: [GitHub - samp-incognito/samp-streamer-plugin](https://github.com/samp-incognito/samp-streamer-plugin/releases)

### YSI-Includes
- Download: [GitHub - pawn-lang/YSI-Includes](https://github.com/pawn-lang/YSI-Includes)

## Funções Principais

```pawn
// Define o clima para uma cidade
SetCityWeather(city, weatherid);

// Atualiza o clima do jogador baseado na localização
UpdatePlayerWeather(playerid);

// Obtém o clima atual de uma cidade
GetCityWeather(city);

// Obtém a cidade atual do jogador
GetPlayerCity(playerid);

// Obtém o nome do clima em português
GetClimaName(weatherid);

// Obtém o nome da cidade
GetCityName(city);

// Obtém o numero de jogadores em uma cidade
GetPlayersInCity(city); 
```
## Demonstração

Um vídeo demonstrativo do sistema está disponível no YouTube. Assista para ver o sistema em funcionamento e entender melhor como ele funciona na prática.

[Assista ao vídeo demonstrativo no YouTube](https://www.youtube.com/watch?v=v_XVzD7FW7g)
## Cidades e Climas

### Cidades
```pawn
E_CITY_LS    // Los Santos
E_CITY_SF    // San Fierro
E_CITY_LV    // Las Venturas
```

### Tipos de Clima
O sistema inclui 21 tipos de clima diferentes.

Exemplos:
```pawn
// Los Angeles (Los Santos)
E_WEATHER_EXTRASUNNY = 0          // Extra Ensolarado
E_WEATHER_SUNNY = 1               // Ensolarado
E_WEATHER_EXTRASUNNY_SMOG = 2     // Extra Ensolarado com Poluição
E_WEATHER_SUNNY_SMOG = 3          // Ensolarado com Poluição
E_WEATHER_CLOUDY = 4              // Nublado

// San Francisco (San Fierro)
E_WEATHER_SUNNY_MILD = 5          // Ensolarado Ameno
E_WEATHER_EXTRASUNNY_MILD = 6     // Extra Ensolarado Ameno
E_WEATHER_CLOUDY_MILD = 7         // Nublado Ameno
E_WEATHER_RAINY = 8               // Chuvoso
E_WEATHER_FOGGY = 9               // Neblina

// Las Vegas (Las Venturas)
E_WEATHER_SUNNY_DRY = 10          // Ensolarado Seco
E_WEATHER_EXTRASUNNY_DRY = 11     // Extra Ensolarado com Ondas de Calor
E_WEATHER_CLOUDY_DRY = 12         // Nublado Seco

// Campo
E_WEATHER_EXTRASUNNY_COUNTRY = 13 // Extra Ensolarado Campo
E_WEATHER_SUNNY_COUNTRY = 14      // Ensolarado Campo
E_WEATHER_CLOUDY_COUNTRY = 15     // Nublado Campo
E_WEATHER_RAINY_COUNTRY = 16      // Chuvoso Campo

// Deserto
E_WEATHER_EXTRASUNNY_DESERT = 17  // Extra Ensolarado Deserto
E_WEATHER_SUNNY_DESERT = 18       // Ensolarado Deserto
E_WEATHER_SANDSTORM = 19          // Tempestade de Areia

// Especial
E_WEATHER_UNDERWATER = 20         // Subaquático (Esverdeado, Nebuloso)
```

## Exemplo de Uso

```pawn
// Definir climas para cada cidade
public OnGameModeInit()
{
    SetCityWeather(E_CITY_LS, E_WEATHER_SUNNY);         // Los Santos: ensolarado
    SetCityWeather(E_CITY_SF, E_WEATHER_FOGGY);         // San Fierro: neblina
    SetCityWeather(E_CITY_LV, E_WEATHER_SUNNY_DESERT);  // Las Venturas: deserto
    return 1;
}
```

## Como Funciona

- O sistema cria áreas dinâmicas para cada cidade no início do gamemode
- Quando um jogador entra em uma cidade, o clima é atualizado automaticamente
- Mais eficiente que sistemas baseados em timer: menos recursos, atualizações instantâneas

## Licença
Use livremente em seus projetos.
