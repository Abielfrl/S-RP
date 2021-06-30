#include <a_samp>
#include <a_mysql>

#include <zcmd>
#include <easydialog>

#include <YSI_Coding/y_hooks>
#include <YSI_Coding/y_va>

#include <YSI_Server/y_colors>

#include <samp_bcrypt>

#include <foreach>

main()
{
    return 1;
}

new MySQL:g_sql;
static g_MysqlRaceCheck[MAX_PLAYERS];

#include "Modules\Server\Define"
#include "Modules\Server\Enum"
#include "Modules\Server\Function"
#include "Modules\Server\Dialog"

#include "Modules\Player\CommandPlayer"

public OnPlayerConnect(playerid)
{
    SendClientMessageEx(playerid, X11_LIGHTBLUE, "SERVER:"WHITE" Welcome %s to this server!", ReturnName(playerid));
    CheckPlayerAccount(playerid);
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    SavePlayerData(playerid);
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

public OnGamemodeExit()
{
    foreach(new i : Player)
    {
        SavePlayerData(i);
    }
    return 1;
}