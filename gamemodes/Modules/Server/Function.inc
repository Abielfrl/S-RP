stock LoadMYSQL()
{
    g_sql = mysql_connect(MYSQL_HOST, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE);

    if(mysql_errno(g_sql) != 0)
    {
        print("[DATA] MySQL Error please check again your plugin");
    }
    else
    {
        print("[DATA] MySQL Loaded");
    }
}

forward OnPlayerLogin(playerid);
public OnPlayerLogin(playerid)
{
    cache_get_value_name_int(0, "ID", PlayerData[playerid][pID]);
    cache_get_value_name_int(0, "Username", PlayerData[playerid][pUsername]);
    cache_get_value_name_int(0, "Password", PlayerData[playerid][pPassword]);
    cache_get_value_name_int(0, "Level", PlayerData[playerid][pLevel]);
    cache_get_value_name_float(0, "PlayerPosX", PlayerData[playerid][pPos][0]);
    cache_get_value_name_float(0, "PlayerPosY", PlayerData[playerid][pPos][1]);
    cache_get_value_name_float(0, "PlayerPosZ", PlayerData[playerid][pPos][2]);
    print("OnPlayerLogin Jalan");
    return 1;
}

//TODO: Kerjain SavePlayerData(playerid)