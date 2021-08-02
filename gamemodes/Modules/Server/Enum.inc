enum e_playerData {
    pID,
    pUsername[MAX_PLAYER_NAME + 1],
    pPassword,
    pCharacter[3],
    pSalt,
    pLevel,
    pGender,
    Float:pPos[3],
    pSkin
};

enum e_vehicleData {
    vID,
    vVehicle,
    vModel,
    vOwner,
    vNos,
    vLock,
    vEngine,
    vTrunk,
    vHood,
    vColor1,
    vColor2,
    Float:vPos[4]
};

new PlayerData[MAX_PLAYERS][e_playerData];
new VehicleData[MAX_VEHICLES][e_vehicleData];