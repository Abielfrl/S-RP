Dialog:Register(playerid, response, listitem, inputtext[])
{
    if(!response)
        return Kick(playerid);
    
    if(strlen(inputtext) < 7)
        return  Dialog_Show(playerid, Register, DIALOG_STYLE_PASSWORD, "Register","ERROR: You must Specify more than 7 Character for Password.","Register","Quit");

    if(strlen(inputtext) > 32)
	    return  Dialog_Show(playerid, Register, DIALOG_STYLE_PASSWORD, "Account Register", "ERROR: You Can't specify more than 32 Character for password.", "Register", "Quit");

    bcrypt_hash(playerid, #OnPlayerPasswordHashed, inputtext, BCRYPT_COST, "i", playerid);
    SetSpawnInfo(playerid, 0, 172, 1769.6141,-1862.0129,13.5768, 0.0, 0, 0, 0, 0, 0, 0);
    SavePlayerData(playerid);
    SpawnPlayer(playerid);
}

Dialog:Login(playerid, response, listitem, inputtext[])
{
    if(!response)
		return Kick(playerid);
	new string[128];
	format(string,sizeof(string),"Welcome back to %s\nPlease input your password to continue:",GetName(playerid));
	if(strlen(inputtext) < 1)
	    return Dialog_Show(playerid, Login, DIALOG_STYLE_PASSWORD, "Account Login", string, "Login", "Cancel");
	new queryCheck[256];
	mysql_format(g_sql, queryCheck, sizeof(queryCheck), "SELECT Password FROM characters WHERE Username = '%e' LIMIT 1", GetName(playerid));
	mysql_query(g_sql, queryCheck);
	new
		hash[BCRYPT_HASH_LENGTH];
	if (cache_num_rows() > 0)
	{
		new 
			hash[BCRYPT_HASH_LENGTH];

		cache_get_value_name(0, "Password", hash, sizeof(hash));
		bcrypt_verify(playerid, #OnPlayerPasswordChecked, inputtext, hash);
	}
	SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2], 0.0, 0, 0, 0, 0, 0, 0);
	SetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
	SpawnPlayer(playerid);
	cache_unset_active();    
}