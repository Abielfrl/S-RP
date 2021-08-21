#include <a_samp>
#include <a_mysql>

#include <zcmd>
#include <easydialog>

#include <YSI_Coding/y_hooks>
#include <YSI_Coding/y_va>

#include <YSI_Server/y_colors>

#include <samp_bcrypt>

#include <foreach>

#include <sscanf2>

main()
{
    printf("Starting server...");
}

new MySQL:g_sql;

#include "Modules\Server\Define"
#include "Modules\Server\Enum"
#include "Modules\Server\Function"
#include "Modules\Server\Dialog"

#include "Modules\Server\Vehicle\Funcs"

#include "Modules\Server\CMD"
#include "Modules\Player\PlayerCMD"

public OnPlayerConnect(playerid)
{
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "SERVER:"WHITE" Welcome %s to State Roleplay server!", ReturnName(playerid));
    CheckPlayerAccount(playerid);
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    TerminateConnection(playerid);
    return 1;
}

public OnGameModeInit()
{
    LoadMYSQL();
    DisableInteriorEnterExits();
    EnableStuntBonusForAll(0);
    SetNameTagDrawDistance(10.0);
    ShowPlayerMarkers(0);
    foreach(new i : Player)
    {
        OnPlayerLogin(i);
    }
    return 1;
}

public OnGameModeExit()
{
    foreach(new i : Player)
    {
        SavePlayerData(i);
        Save_Vehicle(i);
    }
    mysql_close(g_sql);
    return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    return 1;
}