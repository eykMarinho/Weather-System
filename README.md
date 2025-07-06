# Sistema de Clima Dinâmico para SA-MP

## Descrição
Este sistema permite gerenciar climas diferentes para cada cidade do GTA San Andreas (Los Santos, San Fierro e Las Venturas) em seu servidor SA-MP. O sistema detecta automaticamente a localização do jogador e aplica o clima correspondente à cidade em que ele se encontra.

## Características
- Climas específicos para cada cidade
- Detecção automática da cidade do jogador usando áreas dinâmicas
- Atualização instantânea do clima quando o jogador muda de cidade
- Sistema otimizado usando o plugin streamer para melhor desempenho
- 21 tipos diferentes de clima, incluindo:
  - Ensolarado
  - Extra Ensolarado
  - Nublado
  - Chuvoso
  - Neblina
  - Tempestade de Areia
  - Subaquático
  - E muito mais!

## Instalação
1. Certifique-se de ter o plugin streamer instalado em seu servidor
2. Copie o arquivo `WeatherSystem.inc` para a pasta `pawno/include` do seu servidor
3. Inclua o sistema em seu gamemode:
```pawn
#include <streamer>
#include <WeatherSystem.inc>
```

## Funções Disponíveis

### SetCityWeather(city, weatherid)
Define o clima para uma cidade específica.

**Parâmetros:**
- `city`: ID da cidade (E_CITY_LS, E_CITY_SF, E_CITY_LV)
- `weatherid`: ID do clima (E_WEATHER_SUNNY, E_WEATHER_RAINY, etc.)

**Exemplo:**
```pawn
SetCityWeather(E_CITY_LS, E_WEATHER_SUNNY); // Define Los Santos como ensolarado
```

### UpdatePlayerWeather(playerid)
Atualiza o clima para um jogador específico com base em sua localização atual.

**Parâmetros:**
- `playerid`: ID do jogador

### GetCityWeather(city)
Obtém o ID do clima atual de uma cidade.

**Parâmetros:**
- `city`: ID da cidade

**Retorno:**
- ID do clima atual da cidade

### GetPlayerCity(playerid)
Obtém a cidade em que o jogador está atualmente.

**Parâmetros:**
- `playerid`: ID do jogador

**Retorno:**
- ID da cidade (E_CITY_LS, E_CITY_SF, E_CITY_LV)

### GetClimaName(weatherid)
Obtém o nome do clima em português.

**Parâmetros:**
- `weatherid`: ID do clima

**Retorno:**
- Nome do clima em português

### GetCityName(city)
Obtém o nome da cidade.

**Parâmetros:**
- `city`: ID da cidade

**Retorno:**
- Nome da cidade

## Tipos de Clima Disponíveis
```pawn
enum {
    E_WEATHER_EXTRASUNNY = 0,          // Extra Ensolarado (Los Angeles)
    E_WEATHER_SUNNY = 1,               // Ensolarado (Los Angeles)
    E_WEATHER_EXTRASUNNY_SMOG = 2,     // Extra Ensolarado com Poluição (Los Angeles)
    E_WEATHER_SUNNY_SMOG = 3,          // Ensolarado com Poluição (Los Angeles)
    E_WEATHER_CLOUDY = 4,              // Nublado (Los Angeles)
    E_WEATHER_SUNNY_MILD = 5,          // Ensolarado (San Francisco)
    E_WEATHER_EXTRASUNNY_MILD = 6,     // Extra Ensolarado (San Francisco)
    E_WEATHER_CLOUDY_MILD = 7,         // Nublado (San Francisco)
    E_WEATHER_RAINY = 8,               // Chuvoso (San Francisco)
    E_WEATHER_FOGGY = 9,               // Neblina (San Francisco)
    E_WEATHER_SUNNY_DRY = 10,          // Ensolarado (Las Vegas)
    E_WEATHER_EXTRASUNNY_DRY = 11,     // Extra Ensolarado com Ondas de Calor (Las Vegas)
    E_WEATHER_CLOUDY_DRY = 12,         // Nublado (Las Vegas)
    E_WEATHER_EXTRASUNNY_COUNTRY = 13, // Extra Ensolarado (Campo)
    E_WEATHER_SUNNY_COUNTRY = 14,      // Ensolarado (Campo)
    E_WEATHER_CLOUDY_COUNTRY = 15,     // Nublado (Campo)
    E_WEATHER_RAINY_COUNTRY = 16,      // Chuvoso (Campo)
    E_WEATHER_EXTRASUNNY_DESERT = 17,  // Extra Ensolarado (Deserto)
    E_WEATHER_SUNNY_DESERT = 18,       // Ensolarado (Deserto)
    E_WEATHER_SANDSTORM = 19,          // Tempestade de Areia (Deserto)
    E_WEATHER_UNDERWATER = 20           // Subaquático (Esverdeado, Nebuloso)
};
```

## Exemplo de Uso
Veja o arquivo `gamemodes/WeatherSystemExample.pwn` para um exemplo completo de como usar o sistema.

```pawn
// Definir climas para cada cidade no início do gamemode
public OnGameModeInit()
{
    // O sistema já cria automaticamente as áreas dinâmicas para cada cidade
    
    // Definir climas diferentes para cada cidade
    SetCityWeather(E_CITY_LS, E_WEATHER_SUNNY);         // Los Santos com clima ensolarado
    SetCityWeather(E_CITY_SF, E_WEATHER_FOGGY);         // San Fierro com neblina
    SetCityWeather(E_CITY_LV, E_WEATHER_SUNNY_DESERT);  // Las Venturas com clima de deserto
    return 1;
}

// Exibir informações do clima quando o jogador spawnar
public OnPlayerSpawn(playerid)
{
    new cidade = GetPlayerCity(playerid);
    new clima = GetCityWeather(cidade);
    
    printf("Seu clima é %s e sua cidade é %s", GetClimaName(clima), GetCityName(cidade));
    return 1;
}

// O clima será atualizado automaticamente quando o jogador entrar em uma nova cidade
// graças ao callback OnPlayerEnterDynamicArea que é gerenciado internamente pelo sistema
```

## Como Funciona o Sistema de Áreas Dinâmicas
O sistema utiliza áreas dinâmicas do plugin streamer para detectar quando um jogador entra em uma cidade diferente:

1. Três áreas retangulares são criadas no início do gamemode, uma para cada cidade:
   - Los Santos: `-790.0, -3000.0, 3000.0, 548.0`
   - San Fierro: `-3000.0, -3000.0, -784.0, 3000.0`
   - Las Venturas: `-790.0, 548.0, 3000.0, 3000.0`

2. Quando um jogador entra em uma dessas áreas, o callback `OnPlayerEnterDynamicArea` é acionado automaticamente

3. O sistema identifica qual cidade o jogador entrou e atualiza o clima instantaneamente

4. Este método é mais eficiente que o sistema baseado em timer, pois:
   - Consome menos recursos do servidor
   - Atualiza o clima instantaneamente, sem atrasos
   - Só processa a mudança quando realmente necessário

## Licença
Este código é fornecido como está, sem garantias. Você pode usá-lo, modificá-lo e distribuí-lo livremente em seus projetos.

## Créditos
Desenvolvido para servidores SA-MP.
