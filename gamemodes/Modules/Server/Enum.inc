enum e_playerData {
    pID,
    pUsername,
    pPassword,
    pSalt,
    pLevel,
    pGender,
    Float:pPos[3],
    pSkin
};

new PlayerData[MAX_PLAYERS][e_playerData];