/*

____    __    ____  _______     ___   .___________. __    __   _______  .______      
\   \  /  \  /   / |   ____|   /   \  |           ||  |  |  | |   ____| |   _  \     
 \   \/    \/   /  |  |__     /  ^  \ `---|  |----`|  |__|  | |  |__    |  |_)  |    
  \            /   |   __|   /  /_\  \    |  |     |   __   | |   __|   |      /     
   \    /\    /    |  |____ /  _____  \   |  |     |  |  |  | |  |____  |  |\  \----.
    \__/  \__/     |_______/__/     \__\  |__|     |__|  |__| |_______| | _| `._____|
                                                                                      
*/
/*
                    ooooo      ooo       .o.       ooooooooooooo ooooo oooooo     oooo       .o.        .oooooo..o 
                    `888b.     `8'      .888.      8'   888   `8 `888'  `888.     .8'       .888.      d8P'    `Y8 
                    8 `88b.    8      .8"888.          888       888    `888.   .8'       .8"888.     Y88bo.      
                    8   `88b.  8     .8' `888.         888       888     `888. .8'       .8' `888.     `"Y8888o.  
                    8     `88b.8    .88ooo8888.        888       888      `888.8'       .88ooo8888.        `"Y88b 
                    8       `888   .8'     `888.       888       888       `888'       .8'     `888.  oo     .d8P 
                    o8o        `8  o88o     o8888o     o888o     o888o       `8'       o88o     o8888o 8""88888P'  

		native SetCityWeather(city, weatherid);
		native UpdatePlayerWeather(playerid);
		native GetCityWeather(city);
		native GetPlayerCity(playerid);
		native GetClimaName(weatherid);
        native GetCityName(city);
        native GetPlayersInCity(city);                                                              
*/

#if defined _weathersystem_included
	#endinput
#endif
#define _weathersystem_included

        //Includes
#include <streamer>
#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_foreach>

        // Definições
#define E_WEATHER_CITYS  3

enum {
    E_CITY_LS = 0, // Los Santos
    E_CITY_SF = 1, // San Fierro
    E_CITY_LV = 2 // Las Venturas
};

        // Variáveis globais
static  
    g_CityWeather[E_WEATHER_CITYS] = {10, 7, 14}; // Climas padrão: LS=Nublado, SF=Calor, LV=Deserto
    
static 
    g_LastPlayerCity[MAX_PLAYERS],
    STREAMER_TAG_AREA:g_AreaWeather[E_WEATHER_CITYS];

// Tipos de clima
static const g_WeatherTypes[][32] = { 
    "Extra Ensolarado",          // 0 
    "Ensolarado",                // 1 
    "Extra Ensolarado Poluído",  // 2 
    "Ensolarado Poluído",        // 3 
    "Nublado",                   // 4 
    "Ensolarado Ameno",          // 5 
    "Extra Ensolarado Ameno",    // 6 
    "Nublado Ameno",             // 7 
    "Chuvoso",                   // 8 
    "Neblina",                   // 9 
    "Ensolarado Seco",           // 10 
    "Extra Ensolarado Seco",     // 11 
    "Nublado Seco",              // 12 
    "Extra Ensolarado Campo",    // 13 
    "Ensolarado Campo",          // 14 
    "Nublado Campo",             // 15 
    "Chuvoso Campo",             // 16 
    "Extra Ensolarado Deserto", // 17 
    "Ensolarado Deserto",       // 18 
    "Tempestade de Areia",      // 19 
    "Subaquático"               // 20
}; 

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


// Nomes das cidades 
static const g_CityNames[][16] = { 
    "Los Santos", 
    "San Fierro", 
    "Las Venturas" 
};


hook OnGameModeInit() {

    g_AreaWeather[E_CITY_LS] = CreateDynamicRectangle(-790.0, -3000.0, 3000.0, 548.0);
    g_AreaWeather[E_CITY_SF] = CreateDynamicRectangle(-3000.0, -3000.0, -784.0, 3000.0);
    g_AreaWeather[E_CITY_LV] = CreateDynamicRectangle(-790.0, 548.0, 3000.0, 3000.0);

    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerSpawn(playerid) {

    UpdatePlayerWeather(playerid);
    g_LastPlayerCity[playerid] = GetPlayerCity(playerid);

    return Y_HOOKS_CONTINUE_RETURN_1;
}
/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.   
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b  
                    888   .d88'  888       8   888     888  888          888  888          
                    888ooo88P'   888       8   888oooo888'  888          888  888          
                    888          888       8   888    `88b  888          888  888          
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo  
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'  

*/

// Callback para quando o jogador entra em uma área dinâmica
public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid) {
    if(IsPlayerConnected(playerid)) {
        new 
            weather_city = -1;
            
        for(new i = 0; i < E_WEATHER_CITYS; i++) {
            if(areaid == g_AreaWeather[i]) {
                weather_city = i;
                break;
            }
        }
        
        if(weather_city != -1 && weather_city != g_LastPlayerCity[playerid]) {
            g_LastPlayerCity[playerid] = weather_city;
            SetPlayerWeather(playerid, g_CityWeather[weather_city]);
        }
    } 
    return Y_HOOKS_CONTINUE_RETURN_1;
}

/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.     
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o. 
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P' 

*/

stock GetPlayerCity(playerid) {

    for(new i = 0; i < E_WEATHER_CITYS; i++) {

        if(IsPlayerInDynamicArea(playerid, g_AreaWeather[i])) 
            return i;
    }
    return E_CITY_LS; // Padrão para Los Santos
}


stock SetCityWeather(city, weatherid) {
    if(weatherid < 0 || weatherid > 20) return 0; 
    
    g_CityWeather[city] = weatherid;
    foreach(new i : Player) {
        if(GetPlayerCity(i) == city) {
            SetPlayerWeather(i, weatherid);
        }
    }
    return 1;
}

stock GetCityWeather(city) {
    return g_CityWeather[city];
}

stock UpdatePlayerWeather(playerid) {
    if(!IsPlayerConnected(playerid)) 
        return 0;
    
    new city = GetPlayerCity(playerid);
    SetPlayerWeather(playerid, g_CityWeather[city]);
    
    return 1;
}

stock GetClimaName(weatherid) {

    static 
        clima[32]; 

    if(weatherid >= 0 && weatherid <= 20) format(clima, sizeof(clima), "%s", g_WeatherTypes[weatherid]);
    else format(clima, sizeof(clima), "Clima Desconhecido");

    return clima;
}

stock GetCityName(city) {

    static 
        cityname[16]; 
    
    if(city >= 0 && city < sizeof(g_CityNames)) format(cityname, sizeof(cityname), "%s", g_CityNames[city]);
    else format(cityname, sizeof(cityname), "Cidade Desconhecida");
    
    return cityname;
}
stock GetPlayersInCity(city) {
    if(city < 0 || city >= E_WEATHER_CITYS) 
        return 0;
    
    new count = 0;
    foreach(new i : Player) {
        if(GetPlayerCity(i) == city) {
            count++;
        }
    }
    
    return count;
}
