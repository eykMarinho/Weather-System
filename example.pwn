/*
	==============================================
		Exemplo de uso do WeatherSystem.inc
	==============================================
*/

// Includes
#include <a_samp>
#include "..\WeatherSystem.inc"

main() {}


public OnGameModeInit()
{
    // Definir climas diferentes para cada cidade
    SetCityWeather(E_CITY_LS, E_WEATHER_RAINY_COUNTRY);         // Los Santos com clima chuvoso de campo
    SetCityWeather(E_CITY_LV, E_WEATHER_EXTRASUNNY_MILD);       // Las Venturas com clima extra ensolarado ameno
    SetCityWeather(E_CITY_SF, E_WEATHER_SANDSTORM);             // San Fierro com tempestade de areia
    return 1;
}
public OnPlayerSpawn(playerid)
{
    new cidade = GetPlayerCity(playerid);
    new Clima  = GetCityWeather(cidade);
    
    printf("Seu clima e %s sua cidade e %s", GetClimaName(Clima), GetCityName(cidade));
    
    return 1;
}
public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    SetPlayerPos(playerid, fX, fY, fZ);
    return 1;
}
