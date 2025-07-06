#🫧 Sistema de Clima Dinâmico para SA-MP

## O que é?
Sistema que aplica climas diferentes para cada cidade do GTA San Andreas (Los Santos, San Fierro e Las Venturas) com detecção automática da localização do jogador usando áreas dinâmicas.

## Instalação
1. Instale o plugin streamer no servidor
2. Copie `WeatherSystem.inc` para `pawno/include`
3. Inclua no gamemode:
```pawn
#include <streamer>
#include <WeatherSystem.inc>
```

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
E_WEATHER_SUNNY         // Ensolarado
E_WEATHER_RAINY         // Chuvoso
E_WEATHER_FOGGY         // Neblina
E_WEATHER_SANDSTORM     // Tempestade de Areia
E_WEATHER_UNDERWATER    // Subaquático
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
