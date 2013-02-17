#include "pkmnsavestate.h"
#include "pkmnstringreader.h"
#include "pkmnoffsetmanager.h"

#include <fstream>

PkmnSaveState::PkmnSaveState (string filepath, bool backup)
  : _data(NULL), _filepath(filepath), _backup(backup) {

  openFile(filepath);
  /*
  std::ifstream inputFile (_filepath.c_str(), std::ios::binary);
  inputFile.seekg(0, std::ios::end);

  _dataLength = inputFile.tellg();
  _data = new byte[_dataLength];
  
  inputFile.seekg(0, std::ios::beg);
  inputFile.read(reinterpret_cast<char *>(_data), _dataLength);
  inputFile.close();

  if (backup) {
    
    std::string backupFile = filepath + ".bak";
    std::ofstream outputFile (backupFile.c_str(), std::ios::binary | std::ios::trunc);
  
    outputFile.seekp(0, std::ios::beg);
    outputFile.write(reinterpret_cast<char *>(_data), _dataLength);
    outputFile.close();
  }
  */
}

bool PkmnSaveState::saveToFile() const {

  _data[PkmnOffsetManager::getChecksumOffset()] = checksum();

  std::ofstream outputFile (_filepath.c_str(), std::ios::binary | std::ios::trunc);

  outputFile.seekp(0, std::ios::beg);
  outputFile.write(reinterpret_cast<char *>(_data), _dataLength);
  outputFile.close();

  return true;

}

bool PkmnSaveState::openFile(const string &filepath) {

  std::ifstream inputFile;
  inputFile.open(filepath.c_str(), std::ios::binary);
  if (!inputFile.is_open())
    return false;

  // delete older data if any
  // save before deleting?
  if (_data != NULL) {
    delete[] _data;
    _filepath = filepath;
    _dataLength = 0;
  }

  inputFile.seekg(0, std::ios::end);

  _dataLength = inputFile.tellg();
  _data = new byte[_dataLength];

  inputFile.seekg(0, std::ios::beg);
  inputFile.read(reinterpret_cast<char *>(_data), _dataLength);
  inputFile.close();

  if (_backup) {

    std::string backupFile = filepath + ".bak";
    std::ofstream outputFile (backupFile.c_str(), std::ios::binary | std::ios::trunc);

    outputFile.seekp(0, std::ios::beg);
    outputFile.write(reinterpret_cast<char *>(_data), _dataLength);
    outputFile.close();
  }

  return true;

}

int PkmnSaveState::getTrainerId() const {

  return readData(PkmnOffsetManager::getOriginalTrainerIdOffset(), 2);

}

vector<const PkmnSpecies *> PkmnSaveState::getPartyPkmnList() const {

  vector<const PkmnSpecies *> result;

  for (int i=1; i<=6; ++i) {

    int pkmnSpeciesAtIndex = readData(PkmnOffsetManager::getPartyPkmnListOffset(i), 1);
    const PkmnSpecies *activePkmn = PkmnSpeciesList::getById(pkmnSpeciesAtIndex);
    result.push_back(activePkmn);
  }

  return result;

}

int PkmnSaveState::getPartyPkmnCount() const {

  return readData(PkmnOffsetManager::getPartyPkmnCountOffset(), 1);

}

// partyIndex in [1 .. 6]
int PkmnSaveState::getPartyPkmnParameter(int partyIndex, int info) const {

  if (partyIndex > getPartyPkmnCount())
    return 0x00;

  return readData(PkmnOffsetManager::getPartyPkmnParameterOffset(partyIndex, info),
                  PkmnState::getInfoSize(info));

}

// partyIndex in [1 .. 6]
string PkmnSaveState::getPartyPkmnName(int partyIndex) const {

  if (partyIndex > getPartyPkmnCount())
    return "...";

  return PkmnStringReader::toStdString(
        _data + PkmnOffsetManager::getPartyPkmnParameterOffset(partyIndex, PKMNNAME));

}

// partyIndex in [1 .. 6]
PkmnState PkmnSaveState::getPartyPkmnState(int partyIndex) const {

  if (!pkmnExistsAtPartyIndex(partyIndex))
    return PkmnState(NULL, NULL, NULL);

  return PkmnState(
        _data + PkmnOffsetManager::getPartyPkmnParameterOffset(partyIndex, SPECIES),
        _data + PkmnOffsetManager::getPartyPkmnParameterOffset(partyIndex, PKMNNAME),
        _data + PkmnOffsetManager::getPartyPkmnParameterOffset(partyIndex, OTNAME));

}

// partyIndex in [1 .. 6]
bool PkmnSaveState::setPartyPkmnParameter(int partyIndex, int info, int value) {

  if (partyIndex > getPartyPkmnCount())
    return false;

  if (info == SPECIES) {

    _data[PkmnOffsetManager::getPartyPkmnListOffset(partyIndex)] =
        static_cast<byte>(value);
    _data[PkmnOffsetManager::getPartyPkmnParameterOffset(partyIndex, SPECIES)] =
        static_cast<byte>(value);

  } else {

    int infoOffset = PkmnOffsetManager::getPartyPkmnParameterOffset(partyIndex, info);
    for (int i = PkmnState::getInfoSize(info) - 1;
         i >= 0;
         --i) {
      _data[infoOffset + i] = static_cast<byte>(value & 0xFF);
      value = value>>8;
    }

  }

  return true;

}
// partyIndex in [1 .. 6]
// info in [PKMNNAME, OTNAME]
bool PkmnSaveState::setPartyPkmnStrParam(int partyIndex, int info, string value) {

  if (partyIndex > getPartyPkmnCount())
    return false;

  byte *name = PkmnStringReader::fromStdString(value);
  int startingOffset = PkmnOffsetManager::getPartyPkmnParameterOffset(partyIndex, info);
  for (int i=0; i<11; ++i)
    _data[startingOffset + i] = name[i];

  delete[] name;
  return true;

}

// partyIndex in [1 .. 6]
bool PkmnSaveState::createPartyPkmnAtIndex(int partyIndex, int species) {

  // can create pokemon only if the previous (number-1) exist
  for (int i=1; i<partyIndex; i++)
    if (!pkmnExistsAtPartyIndex(i))
      return false;
  if (pkmnExistsAtPartyIndex(partyIndex))
    return false;

  // :: reserve room in the 'party area' ::
  // increase pkmn number in party
  _data[PkmnOffsetManager::getPartyPkmnCountOffset()] =
      static_cast<byte>(_data[PkmnOffsetManager::getPartyPkmnCountOffset()] + 1);

  // shifting end-party flag
  _data[PkmnOffsetManager::getPartyPkmnListOffset(partyIndex) + 1] =
    static_cast<byte>(0xFF);

  // :: set default value for newly created pokemon ::
  setPartyPkmnStrParam (partyIndex, PKMNNAME, PkmnSpeciesList::getById(species)->getUpperCaseName());
  setPartyPkmnStrParam (partyIndex, OTNAME,   "CACCA");
  setPartyPkmnParameter(partyIndex, SPECIES,  species);
  setPartyPkmnParameter(partyIndex, LEVELN,   0x01);
  setPartyPkmnParameter(partyIndex, TRAINER,  getTrainerId());
  setPartyPkmnParameter(partyIndex, EXP,      0x01);
  setPartyPkmnParameter(partyIndex, LEVEL,    0x01);
  
  return true;

}

// number in [1 .. 6]
bool PkmnSaveState::deletePartyPkmnAtIndex(int index) {

  if (!pkmnExistsAtPartyIndex(index))
    return false;
  // cannot delete last pokemon
  if (readData(PkmnOffsetManager::getPartyPkmnCountOffset(), 1) == 1)
    return false;

  // :: decrease pkmn number in party
  _data[PkmnOffsetManager::getPartyPkmnCountOffset()] =
      static_cast<byte>(_data[PkmnOffsetManager::getPartyPkmnCountOffset()] - 1);
    
  // :: shifting pkmn information to fill cleared data locations
  for (int i=index; i<=6; ++i) {
  
    // shifting 'party area'
    _data[PkmnOffsetManager::getPartyPkmnListOffset(i)] =
        _data[PkmnOffsetManager::getPartyPkmnListOffset(i+1)];
    
    if (i<6) {
      // shifting 'stats area'
      for (int j=0; j<44; ++j)
        _data[PkmnOffsetManager::getPartyPkmnParameterOffset(i, SPECIES)+j] =
            _data[PkmnOffsetManager::getPartyPkmnParameterOffset(i+1, SPECIES)+j];
    
      // shifting 'names area' and 'original trainer name area'
      for (int j=0; j<11; ++j) {
        _data[PkmnOffsetManager::getPartyPkmnParameterOffset(i, PKMNNAME)+j] =
            _data[PkmnOffsetManager::getPartyPkmnParameterOffset(i+1, PKMNNAME)+j];

        _data[PkmnOffsetManager::getPartyPkmnParameterOffset(i, OTNAME)+j] =
            _data[PkmnOffsetManager::getPartyPkmnParameterOffset(i+1, OTNAME)+j];
      }

    }
  }
  
  // :: deleting last memory location
  _data[PkmnOffsetManager::getPartyPkmnListOffset(6) + 1] = static_cast<byte>(0x00);
  for (int j=0; j<44; ++j)
    _data[PkmnOffsetManager::getPartyPkmnParameterOffset(6, SPECIES)+j] = static_cast<byte>(0x00);
  for (int j=0; j<11; ++j) {
    _data[PkmnOffsetManager::getPartyPkmnParameterOffset(6, PKMNNAME)+j] = static_cast<byte>(0x00);
    _data[PkmnOffsetManager::getPartyPkmnParameterOffset(6, OTNAME)+j] = static_cast<byte>(0x00);
  }

  return true;

}

byte PkmnSaveState::checksum () const {

  byte t = 0x00;
  for (int i= 0x2598; i<0x3523; i++) {
    t = static_cast<byte>(t + (_data[i] & 0xFF));
  }
  
  return static_cast<byte>(t ^ 0xFF);
}


//  index in [1 .. 6]
bool PkmnSaveState::pkmnExistsAtPartyIndex (int index) const {

  if (index < 1 || index > 6) {
    return false;
  }

  if (readData(PkmnOffsetManager::getPartyPkmnListOffset(index), 1) == 0xFF) {
    return false;
  }
  return true;

}


// POKEDEX INFO

PkmnPokedex PkmnSaveState::getPkmnPokedex() const {
  return PkmnPokedex(
        &_data[PkmnSaveState::POKEDEX_PKMN_SEEN_OFFSET],
        &_data[PkmnSaveState::POKEDEX_PKMN_CATCH_OFFSET]);
}
bool PkmnSaveState::setPkmnPokedexSeen(int pkmnIndex, bool isSeen) {

  pkmnIndex = pkmnIndex - 1;
  int mask = 0x01<<(pkmnIndex % 8);
  if (isSeen) {
    _data[PkmnSaveState::POKEDEX_PKMN_SEEN_OFFSET + pkmnIndex/8] |= mask;
  } else {
    _data[PkmnSaveState::POKEDEX_PKMN_SEEN_OFFSET + pkmnIndex/8] &= ~mask;
  }
  return true;

}
bool PkmnSaveState::setPkmnPokedexCatched(int pkmnIndex, bool isCatched) {

  pkmnIndex = pkmnIndex - 1;
  int mask = 0x01<<(pkmnIndex % 8);
  if (isCatched) {
    _data[PkmnSaveState::POKEDEX_PKMN_CATCH_OFFSET + pkmnIndex/8] |= mask;
  } else {
    _data[PkmnSaveState::POKEDEX_PKMN_CATCH_OFFSET + pkmnIndex/8] &= ~mask;
  }
  return true;

}

int PkmnSaveState::readData(int byteOffset, int numByte) const {

  int result = 0;
  for (int i=0; i<numByte; ++i) {
    result = ((result<<8) & 0xFFFFFF00) | (_data[byteOffset+i] & 0xFF);
  }
  return result;

}
