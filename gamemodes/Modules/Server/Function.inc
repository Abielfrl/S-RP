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

stock GetName(playerid)
{
	new name[MAX_PLAYER_NAME];
 	GetPlayerName(playerid,name,sizeof(name));
	return name;
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
    cache_get_value_name_int(0, "Skin", PlayerData[playerid][pSkin]);
    print("OnPlayerLogin Jalan");
    return 1;
}

stock SavePlayerData(playerid)
{
    GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);  
    new query[1012];
    mysql_format(g_sql, query, sizeof(query), "UPDATE `characters` SET `Level` = '%d', `PlayerPosX`='%.4f', `PlayerPosY`='%.4f', `PlayerPosZ`='%.4f', `Skin` = '%d', `Password` = '%s', WHERE `Username` = '%s'",
    PlayerData[playerid][pLevel],
    PlayerData[playerid][pPos][0],
    PlayerData[playerid][pPos][1],
    PlayerData[playerid][pPos][2],
    PlayerData[playerid][pSkin],
    PlayerData[playerid][pPassword],
    GetName(playerid)
    );
    mysql_tquery(g_sql, query);
    print("[DATA] Save data for");
    return 1;
}

forward OnPlayerPasswordHashed(playerid);
public OnPlayerPasswordHashed(playerid)
{
    new 
        query[512],
        hash[BCRYPT_HASH_LENGTH + 1];
    bcrypt_get_hash(hash, sizeof(hash));
	mysql_format(g_sql,query,sizeof(query),"INSERT INTO `characters` (`Username`,`Password`) VALUES('%e','%e')", GetName(playerid), hash);
    mysql_query(g_sql, query, false);
    SetSpawnInfo(playerid, 0, 172, 1769.6141,-1862.0129,13.5768, 0.0, 0, 0, 0, 0, 0, 0);
    SavePlayerData(playerid);
    SpawnPlayer(playerid);
    return 1;
}

forward OnPlayerPasswordChecked(playerid, bool:success);
public OnPlayerPasswordChecked(playerid, bool:success)
{
    new string[128];
    format(string, sizeof(string), "Welcome back to State Cops And Robbery %s\nPlease input your password to join", GetName(playerid));
    if(!success)
        return Dialog_Show(playerid, Login, DIALOG_STYLE_PASSWORD, "Login to Server", string, "Select", "Cancel");
    OnPlayerLogin(playerid);
    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2], 0.0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "SERVER"WHITE" Sukses masuk ke dalam server");
    return 1;
}

stock CheckPlayerAccount(playerid)
{
    new query[256];
    mysql_format(g_sql, query, sizeof(query), "SELECT * FROM `characters` WHERE `Username` = '%e' LIMIT 1", GetName(playerid));
    mysql_tquery(g_sql, query, "OnQueryFinished", "d", playerid);
}

forward OnQueryFinished(playerid);
public OnQueryFinished(playerid)
{
    new string[512];
    if(cache_num_rows() > 0)
    {
        cache_get_value_name_int(0, "ID", PlayerData[playerid][pID]);
        format(string, sizeof(string), "Welcome back to State Cops And Robbery %s\nPlease input your password to join", GetName(playerid));
        Dialog_Show(playerid, Login, DIALOG_STYLE_PASSWORD, "State Roleplay", string, "Login", "Cancel");
    }
    else
    {
        format(string, sizeof(string), "Welcome to State Cops And Robbery\nPlease create the account to login this server\nInput the password");
        Dialog_Show(playerid, Register, DIALOG_STYLE_PASSWORD, "State Roleplay", string, "Register", "Cancel");
    }
    return 1;
}

SendClientMessageEx(playerid, colour, const text[], va_args<>)
{
    new str[145];
    va_format(str, sizeof(str), text, va_start<3>);
    return SendClientMessage(playerid, colour, str);
}

PlayerHelp(playerid)
{
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "PLAYER:"WHITE" /help");
}

ReturnName(playerid)
{
    new
        returnNames[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, returnNames, sizeof(returnNames));
    return returnNames;
}

stock SaveFirstPlayer(playerid)
{
	PlayerData[playerid][pLevel] = 1;
    PlayerData[playerid][pSkin] = 0;
	PlayerData[playerid][pPos][0] = 1769.6141;
	PlayerData[playerid][pPos][1] = 1862.0129;
	PlayerData[playerid][pPos][2] = 13.5768;
	SetPlayerValidScore(playerid, PlayerData[playerid][pLevel]);
	print("SaveFirstPlayer Called");
	return 1;
}

stock SetPlayerValidScore(playerid, amount)
{
	PlayerData[playerid][pLevel] += amount;
	SetPlayerScore(playerid, PlayerData[playerid][pLevel]);
	return 1;
}