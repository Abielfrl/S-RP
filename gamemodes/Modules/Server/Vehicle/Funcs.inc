function Save_Vehicle(playerid)
{
	new i = GetPlayerVehicleID(playerid);
	GetVehiclePos(i, VehicleData[i][vPos][0], VehicleData[i][vPos][1], VehicleData[i][vPos][2]);
	GetVehicleZAngle(i, VehicleData[i][vPos][3]);
	new query[512];
	mysql_format(g_sql, query, sizeof(query), "UPDATE `vehicle` SET `Model` = '%d', `Owner` = '%d', `Nos` = '%d', `Lock` = '%d', `Engine` = '%d', `Trunk` = '%d', `Hood` = '%d', `PosX` = '%.4f', `PosY` = '%.4f', `PosZ` = '%.4f', `PosA` = '%.4f', `Color1` = '%d', `Color2` = '%d' WHERE `ID` = '%d'",
	VehicleData[i][vModel],
	VehicleData[i][vOwner],
	VehicleData[i][vNos],
	VehicleData[i][vLock],
	VehicleData[i][vEngine],
	VehicleData[i][vTrunk],
	VehicleData[i][vHood],
	VehicleData[i][vPos][0],
	VehicleData[i][vPos][1],
	VehicleData[i][vPos][2],
	VehicleData[i][vPos][3],
	VehicleData[i][vColor1],
	VehicleData[i][vColor2],
	VehicleData[i][vID]);
	mysql_tquery(g_sql, query);
	printf("[DATA] Vehicle has been Saved.");
	return 1;
}

function Load_Vehicle(playerid)
{
	new query[128];
	mysql_format(g_sql, query, sizeof(query), "SELECT * FROM `vehicle` WHERE `Owner` = %d", PlayerData[playerid][pID]);
	mysql_query(g_sql, query, true);

	new count = cache_num_rows();
	if(count > 0)
	{
		for(new z = 0; z < count; z++)
		{
			new i = GetPlayerVehicleID(playerid);
			cache_get_value_name_int(z, "ID", VehicleData[i][vID]);
			cache_get_value_name_int(z, "Model", VehicleData[i][vModel]);
			cache_get_value_name_int(z, "Owner", VehicleData[i][vOwner]);
			cache_get_value_name_int(z, "Nos", VehicleData[i][vNos]);
			cache_get_value_name_int(z, "Lock", VehicleData[i][vLock]);
			cache_get_value_name_int(z, "Engine", VehicleData[i][vEngine]);
			cache_get_value_name_int(z, "Trunk", VehicleData[i][vTrunk]);
			cache_get_value_name_int(z, "Hood", VehicleData[i][vHood]);
			cache_get_value_name_float(z, "PosX", VehicleData[i][vPos][0]);
			cache_get_value_name_float(z, "PosY", VehicleData[i][vPos][1]);
			cache_get_value_name_float(z, "PosZ", VehicleData[i][vPos][2]);
			cache_get_value_name_float(z, "PosA", VehicleData[i][vPos][3]);
			cache_get_value_name_int(z, "Color1", VehicleData[i][vColor1]);
			cache_get_value_name_int(z, "Color2", VehicleData[i][vColor2]);
		}
		printf("[VEHICLE] Loaded player vehicle from: %s(%d)", PlayerData[playerid][pUsername], playerid);
	}
	return 1;
}

function OnCarCreated(vehicleid)
{
	if (vehicleid == -1)
	    return 0;

	VehicleData[vehicleid][vID] = cache_insert_id();
	Save_Vehicle(vehicleid);

	return 1;
}

function Vehicle_Create(playerid, ownerid, modelid, Float:x, Float:y, Float:z, Float:a, color1, color2)
{
	new i = GetPlayerVehicleID(playerid);
	VehicleData[i][vID] = cache_insert_id();
	VehicleData[i][vOwner] = ownerid;
	VehicleData[i][vModel] = modelid; 
	VehicleData[i][vPos][0] = x;
	VehicleData[i][vPos][1] = y;
	VehicleData[i][vPos][2] = z;
	VehicleData[i][vPos][3] = a;
	VehicleData[i][vColor1] = color1;
	VehicleData[i][vColor2] = color2;
	VehicleData[i][vNos] = 0;
	VehicleData[i][vLock] = 0;
	VehicleData[i][vEngine] = 0;
	VehicleData[i][vTrunk] = 0;
	VehicleData[i][vHood] = 0;
	VehicleData[i][vVehicle] = CreateVehicle(modelid, x, y, z, a, color1, color2, -1);
	// Save_Vehicle(playerid);
    mysql_tquery(g_sql, "INSERT INTO `cars` (`carModel`) VALUES(0)", "OnCarCreated", "d", i);
	return -1;
}