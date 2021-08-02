CMD:givecar(playerid, params[])
{
    static
        userid,
        Model[32];

    if(sscanf(params, "us[32]", userid, Model))
        return SendClientMessageEx(playerid, X11_LIGHTBLUE, "USAGE:"WHITE"/givecar [playerid/PartOfName] [ModelID]");

    if((Model[0] = GetVehicleModelByName(Model)) == 0)
        return SendErrorMessage(playerid, "Invalid model");

    new
        Float:x,
        Float:y,
        Float:z,
        Float:a;

    GetPlayerPos(userid, x, y, z);
    GetPlayerFacingAngle(userid, a);

    new id = Vehicle_Create(playerid, PlayerData[userid][pID], Model[0], x, y + 2, z + 1, a, random(127), random(127));
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "SERVER: "WHITE"Kamu telah membuat kendarana %d", Model);
    return 1;
}