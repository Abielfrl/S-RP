CMD:givecar(playerid, params[])
{
    static
        userid,
        Model[32],
        Color1[32],
        Color2[32];

    if(sscanf(params, "us[32]s[32]s[32]", userid, Model, Color1, Color2))
        return SendClientMessageEx(playerid, X11_LIGHTBLUE, "USAGE:"WHITE"/givecar [playerid/PartOfName] [modelid] [color1] [color2]");

    if((Model[0] = GetVehicleModelByName(Model)) == 0)
        return SendErrorMessage(playerid, "Invalid model");

    new
        Float:x,
        Float:y,
        Float:z,
        Float:a;

    GetPlayerPos(userid, x, y, z);
    GetPlayerFacingAngle(userid, a);

    Vehicle_Create(playerid, PlayerData[userid][pID], Model[0], x, y + 2, z + 1, a, Color1, Color2);
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "SERVER: "WHITE"Kamu telah membuat kendarana %d", Model);
    return 1;
}