#include "pkmnoffsetmanager.h"
#include "pkmnstate.h"

int PkmnOffsetManager::getPartyPkmnCountOffset() {
  int result = 0;
  result = PkmnOffsetManager::PARTY_START_OFFSET +
      PkmnOffsetManager::getPartyDataOffset(PKMNCOUNTDATA);
  return result;
}

// partyIndex in [1 .. 6]
int PkmnOffsetManager::getPartyPkmnListOffset(int partyIndex) {
  int result = 0;
  result = PkmnOffsetManager::PARTY_START_OFFSET +
      PkmnOffsetManager::getPartyDataOffset(PKMNSPECIESLISTDATA) +
      (partyIndex - 1);
  return result;
}

int PkmnOffsetManager::getPartyPkmnParameterOffset(int partyIndex, int info) {
  int result = 0;
  if (info == PKMNNAME) {
    result = PkmnOffsetManager::PARTY_START_OFFSET +
        PkmnOffsetManager::getPartyDataOffset(PKMNNAMEDATA) +
        11*(partyIndex - 1);
  } else if (info == OTNAME) {
    result = PkmnOffsetManager::PARTY_START_OFFSET +
        PkmnOffsetManager::getPartyDataOffset(PKMNOTNAMEDATA) +
        11*(partyIndex - 1);
  } else {
    result = PkmnOffsetManager::PARTY_START_OFFSET +
        44*(partyIndex - 1) +
        PkmnOffsetManager::getPartyDataOffset(PKMNSTATSDATA) +
        PkmnState::getOffset(info);
  }
  return result;
}

int PkmnOffsetManager::getCurrentBoxNumberOffset() {
  int result = 0;
  result = PkmnOffsetManager::CURRENT_BOX_NUMBER_OFFSET;
  return result;
}

// boxIndex in [1 .. 12]
int PkmnOffsetManager::getBoxPkmnCountOffset(
    int boxIndex,
    int currentBox) {

  int result = 0;
  if (boxIndex == currentBox)
    result = PkmnOffsetManager::CURRENT_BOX_START_OFFSET +
        PkmnOffsetManager::getBoxDataOffset(PKMNCOUNTDATA);
  else {
    int boxStoredPosition = 0;
    if (boxIndex < currentBox) boxStoredPosition = boxIndex - 1;
    else boxStoredPosition = boxIndex - 2;

    if (boxStoredPosition < 6) result = PkmnOffsetManager::STORED_BOX_START_OFFSET1;
    else result = PkmnOffsetManager::STORED_BOX_START_OFFSET2;

    result = result + 1122 * (boxStoredPosition % 6)
             + PkmnOffsetManager::getBoxDataOffset(PKMNCOUNTDATA);
  }
  /*
  else if (boxIndex < currentBox)
    result = PkmnOffsetManager::STORED_BOX_START_OFFSET +
        1122 * (boxIndex - 1) +
        PkmnOffsetManager::getBoxDataOffset(PKMNCOUNTDATA);
  else if (boxIndex > currentBox)
    result = PkmnOffsetManager::STORED_BOX_START_OFFSET +
        1122 * (boxIndex - 2) +
        PkmnOffsetManager::getBoxDataOffset(PKMNCOUNTDATA);
  */
  return result;

}

int PkmnOffsetManager::getBoxPkmnListOffset(
    int boxIndex,
    int pkmnIndex,
    int currentBox) {
/*
  int result = 0;
  if (boxIndex == currentBox)
    result = PkmnOffsetManager::CURRENT_BOX_START_OFFSET +
        PkmnOffsetManager::getBoxDataOffset(PKMNSPECIESLISTDATA) +
        (pkmnIndex - 1);
  else if (boxIndex < currentBox)
    result = PkmnOffsetManager::STORED_BOX_START_OFFSET +
        1122 * (boxIndex - 1) +
        PkmnOffsetManager::getBoxDataOffset(PKMNSPECIESLISTDATA) +
        (pkmnIndex - 1);
  else if (boxIndex > currentBox)
    result = PkmnOffsetManager::STORED_BOX_START_OFFSET +
        1122 * (boxIndex - 2) +
        PkmnOffsetManager::getBoxDataOffset(PKMNSPECIESLISTDATA) +
        (pkmnIndex - 1);
  return result;*/

  int result = 0;
  if (boxIndex == currentBox)
    result = PkmnOffsetManager::CURRENT_BOX_START_OFFSET;
  else {
    int boxStoredPosition = 0;
    if (boxIndex < currentBox) boxStoredPosition = boxIndex - 1;
    else boxStoredPosition = boxIndex - 2;

    if (boxStoredPosition < 6) result = PkmnOffsetManager::STORED_BOX_START_OFFSET1;
    else result = PkmnOffsetManager::STORED_BOX_START_OFFSET2;

    result = result + 1122 * (boxStoredPosition % 6);
  }
  result += PkmnOffsetManager::getBoxDataOffset(PKMNSPECIESLISTDATA) +
            (pkmnIndex - 1);
  return result;

}

int PkmnOffsetManager::getBoxPkmnParameterOffset(
    int boxIndex,
    int pkmnIndex,
    int paramInfo,
    int currentBox) {

  if (paramInfo & (MAXHP | ATT | DEF | SPD | SPC | LEVEL))
    return 0;

  int result = 0;
  if (boxIndex == currentBox)
    result = PkmnOffsetManager::CURRENT_BOX_START_OFFSET;
  else {
    int boxStoredPosition = 0;
    if (boxIndex < currentBox) boxStoredPosition = boxIndex - 1;
    else boxStoredPosition = boxIndex - 2;

    if (boxStoredPosition < 6) result = PkmnOffsetManager::STORED_BOX_START_OFFSET1;
    else result = PkmnOffsetManager::STORED_BOX_START_OFFSET2;

    result = result + 1122 * (boxStoredPosition % 6);
  }
  /*
  else if (boxIndex < currentBox)
    result = PkmnOffsetManager::STORED_BOX_START_OFFSET +
        1122 * (pkmnIndex - 1);
  else if (boxIndex > currentBox)
    result = PkmnOffsetManager::STORED_BOX_START_OFFSET +
        1122 * (pkmnIndex - 2);*/

  if (paramInfo == PKMNNAME)
    result += PkmnOffsetManager::getBoxDataOffset(PKMNNAMEDATA) +
        11 * (pkmnIndex - 1);
  else if (paramInfo== OTNAME)
    result += PkmnOffsetManager::getBoxDataOffset(PKMNOTNAMEDATA) +
        11 * (pkmnIndex - 1);
  else
    result += PkmnOffsetManager::getBoxDataOffset(PKMNSTATSDATA) +
        33 * (pkmnIndex - 1) +
        PkmnState::getOffset(paramInfo);

  return result;

}

int PkmnOffsetManager::getOriginalTrainerNameOffset() {
  return PkmnOffsetManager::ORIGINAL_TRAINER_NAME_OFFSET;
}

int PkmnOffsetManager::getOriginalTrainerIdOffset() {
  return PkmnOffsetManager::ORIGINAL_TRAINER_ID_OFFSET;
}

int PkmnOffsetManager::getNemesisTrainerNameOffset() {
  return PkmnOffsetManager::NEMESIS_TRAINER_NAME_OFFSET;
}

int PkmnOffsetManager::getMoneyOffset() {
  return PkmnOffsetManager::MONEY_OFFSET;
}

int PkmnOffsetManager::getChecksumOffset() {
  return PkmnOffsetManager::CHECKSUM_OFFSET;
}

// Returns the number of bytes that precede the speciefied info
// from the starting point of Party/Box Data
int PkmnOffsetManager::getPartyDataOffset(int info) {
  int result = 0;
  if (info == PKMNCOUNTDATA)            result = 0x0000;
  else if (info == PKMNSPECIESLISTDATA) result = 0x0001;
  else if (info == PKMNSTATSDATA)       result = 0x0008;
  else if (info == PKMNOTNAMEDATA)      result = 0x0110;
  else if (info == PKMNNAMEDATA)        result = 0x0152;
  return result;
}

int PkmnOffsetManager::getBoxDataOffset(int info) {
  int result = 0;
  if (info == PKMNCOUNTDATA)            result = 0x0000;
  else if (info == PKMNSPECIESLISTDATA) result = 0x0001;
  else if (info == PKMNSTATSDATA)       result = 0x0016;
  else if (info == PKMNOTNAMEDATA)      result = 0x02AA;
  else if (info == PKMNNAMEDATA)        result = 0x0386;
  return result;
}
