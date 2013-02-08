#include "pkmnsavestate.h"
#include "pkmnstringreader.h"

#include <fstream>

PkmnSaveState::PkmnSaveState (string filepath, bool backup) : 
    _filepath(filepath) {

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

}

bool PkmnSaveState::saveToFile() const {

  _data[PkmnSaveState::CHECKSUM_OFFSET] = checksum();

  std::ofstream outputFile (_filepath.c_str(), std::ios::binary | std::ios::trunc);

  outputFile.seekp(0, std::ios::beg);
  outputFile.write(reinterpret_cast<char *>(_data), _dataLength);
  outputFile.close();

  return true;

}

int PkmnSaveState::getTrainerId() const {

  return static_cast<int>(((_data[PkmnSaveState::TRAINER_OFFSET]<<8)&0xFF00) +
                           (_data[PkmnSaveState::TRAINER_OFFSET + 1]&0x00FF));

}

vector<const PkmnSpecies *> PkmnSaveState::getPartyPkmnList() const {

  vector<const PkmnSpecies *> result;

  for (int i=0; i<6; ++i) {
    const PkmnSpecies *activePkmn =
      PkmnSpeciesList::get(_data[PkmnSaveState::PARTY_PKMN_SPECIES_OFFSET + i] & 0xFF);
    result.push_back(activePkmn);
  }

  return result;

}

int PkmnSaveState::getPartyPkmnCount() const {

  return static_cast<int>(_data[PkmnSaveState::PARTY_PKMN_COUNT_OFFSET]);

}

// partyIndex in [1 .. 6]
int PkmnSaveState::getPartyPkmnParameter(int partyIndex, int info) const {

  if (partyIndex > getPartyPkmnCount())
    return 0x00;

  int result = 0;
  int startingOffset = PkmnState::getOffset(info);

  for (int i=0; i<PkmnState::getInfoSize(info); i++) {
    result = (result<<8) |
        (_data[PkmnSaveState::PARTY_PKMN_STATE_OFFSET +
              44*(partyIndex-1) + startingOffset + i] & 0xFF);
  }

  return result;

}

// partyIndex in [1 .. 6]
string PkmnSaveState::getPartyPkmnName(int partyIndex) const {

  if (partyIndex > getPartyPkmnCount())
    return "...";

  return PkmnStringReader::toStdString(_data +
                                       PkmnSaveState::PARTY_PKMN_NAMES_OFFSET +
                                       11*(partyIndex-1));

}

// partyIndex in [1 .. 6]
PkmnState* PkmnSaveState::getPartyPkmnState(int partyIndex) const {

  if (!pkmnExistsAtPartyIndex(partyIndex))
    return NULL;

  return new PkmnState(
    &( _data[PkmnSaveState::PARTY_PKMN_STATE_OFFSET + 44*(partyIndex-1)] ),
    &( _data[PkmnSaveState::PARTY_PKMN_NAMES_OFFSET + 11*(partyIndex-1)] ));
}

// partyIndex in [1 .. 6]
bool PkmnSaveState::setPartyPkmnParameter(int partyIndex, int info, int value) {

  if (partyIndex > getPartyPkmnCount())
    return false;

  if (info == SPECIES) {

    // Need to set species in party list and pkmnstate
    // Need to update pkmn type in pkmnstate
    _data[PkmnSaveState::PARTY_PKMN_SPECIES_OFFSET + partyIndex - 1] =
        static_cast<byte>(value);
    int startingOffset = PkmnSaveState::PARTY_PKMN_STATE_OFFSET + 44*(partyIndex-1);
    _data[startingOffset + PkmnState::getOffset(SPECIES)] =
        static_cast<byte>(value);
    _data[startingOffset + PkmnState::getOffset(TYPE1)] =
        PkmnSpeciesList::get(value)->getElement1();
    _data[startingOffset + PkmnState::getOffset(TYPE2)] =
        PkmnSpeciesList::get(value)->getElement2();

  } else {

    int startingOffset = PkmnSaveState::PARTY_PKMN_STATE_OFFSET +
        44*(partyIndex-1) + PkmnState::getOffset(info);
    for (int i=PkmnState::getInfoSize(info)-1; i>=0; i--) {
      _data[startingOffset + i] = static_cast<byte>(value & 0xFF);
      value = value>>8;
    }

  }

  return true;

}
// partyIndex in [1 .. 6]
bool PkmnSaveState::setPartyPkmnName(int partyIndex, string value) {

  if (partyIndex > getPartyPkmnCount())
    return false;

  byte *name = PkmnStringReader::fromStdString(value);
  int startingOffset = PkmnSaveState::PARTY_PKMN_NAMES_OFFSET + 11*(partyIndex-1);
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
  _data[PkmnSaveState::PARTY_PKMN_COUNT_OFFSET] =
    static_cast<byte>(_data[PkmnSaveState::PARTY_PKMN_COUNT_OFFSET] + 1);
  // shifting end-party flag
  //  _data[PkmnSaveState::PARTY_PKMN_SPECIES_OFFSET + partyIndex - 1] =
  //    static_cast<byte>(species);
  _data[PkmnSaveState::PARTY_PKMN_SPECIES_OFFSET + partyIndex] =
    static_cast<byte>(0xFF);

  // :: set default value for newly created pokemon ::
  setPartyPkmnName(partyIndex, PkmnSpeciesList::get(species)->getName());
  setPartyPkmnParameter(partyIndex, SPECIES, species);
  setPartyPkmnParameter(partyIndex, HP,        0x0A);
  setPartyPkmnParameter(partyIndex, LEVELN,    0x01);
  setPartyPkmnParameter(partyIndex, MOVE1,     0x01);
  setPartyPkmnParameter(partyIndex, TRAINER,   getTrainerId());
  setPartyPkmnParameter(partyIndex, EXP,       0x01);
  setPartyPkmnParameter(partyIndex, MOVE1PP,   0x01);
  setPartyPkmnParameter(partyIndex, LEVEL,     0x01);
  setPartyPkmnParameter(partyIndex, MAXHP,     0x0A);
  setPartyPkmnParameter(partyIndex, ATT,       0x05);
  setPartyPkmnParameter(partyIndex, DEF,       0x05);
  setPartyPkmnParameter(partyIndex, SPD,       0x05);
  setPartyPkmnParameter(partyIndex, SPC,       0x05);
  
  return true;

}

// number in [1 .. 6]
bool PkmnSaveState::deletePartyPkmnAtIndex(int index) {

  if (!pkmnExistsAtPartyIndex(index))
    return false;
  // cannot delete last pokemon
  if (_data[PkmnSaveState::PARTY_PKMN_COUNT_OFFSET] == 1)
    return false;

  // :: decrease pkmn number in party
  _data[PkmnSaveState::PARTY_PKMN_COUNT_OFFSET] =
    static_cast<byte>(_data[PkmnSaveState::PARTY_PKMN_COUNT_OFFSET] - 1);
    
  // :: shifting pkmn information to fill cleared data locations
  for (int i=index-1; i<6; ++i) {
  
    // shifting 'party area'
    _data[PkmnSaveState::PARTY_PKMN_SPECIES_OFFSET + i] =
      _data[PkmnSaveState::PARTY_PKMN_SPECIES_OFFSET + i + 1];
    
    if (i<5) {
      // shifting 'stats area'
      for (int j=0; j<44; ++j)
        _data[PkmnSaveState::PARTY_PKMN_STATE_OFFSET + i*44 + j] =
          _data[PkmnSaveState::PARTY_PKMN_STATE_OFFSET + (i+1)*44 + j];
    
      // shifting 'names area'
      for (int j=0; j<11; ++j)
        _data[PkmnSaveState::PARTY_PKMN_NAMES_OFFSET + i*11 + j] =
          _data[PkmnSaveState::PARTY_PKMN_NAMES_OFFSET + (i+1)*11 + j];
    }
  }
  
  // :: deleting last memory location
  _data[PkmnSaveState::PARTY_PKMN_SPECIES_OFFSET + 6] = static_cast<byte>(0x00);
  for (int j=0; j<44; ++j)
    _data[PkmnSaveState::PARTY_PKMN_STATE_OFFSET + 5*44 + j] = static_cast<byte>(0x00);
  for (int j=0; j<11; ++j)
    _data[PkmnSaveState::PARTY_PKMN_NAMES_OFFSET + 5*11 + j] = static_cast<byte>(0x00);

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

  if ((_data[PkmnSaveState::PARTY_PKMN_SPECIES_OFFSET + index - 1] & 0xFF) == 0xFF) {
//      || _data[PkmnSaveState::BELT_PKMN_SPCS_OFFSET + index - 1] == 0x00 )
    return false;
  }
  return true;

}


// POKEDEX INFO

PkmnPokedex PkmnSaveState::getPkmnPokedex() const {
  return PkmnPokedex(
        &_data[PkmnSaveState::PKMN_POKEDEX_SEEN_OFFSET],
        &_data[PkmnSaveState::PKMN_POKEDEX_CATCH_OFFSET]);
}
bool PkmnSaveState::setPkmnPokedexSeen(int pkmnIndex, bool isSeen) {

  pkmnIndex = pkmnIndex - 1;
  int mask = 0x01<<(pkmnIndex % 8);
  if (isSeen) {
    _data[PkmnSaveState::PKMN_POKEDEX_SEEN_OFFSET + pkmnIndex/8] |= mask;
  } else {
    _data[PkmnSaveState::PKMN_POKEDEX_SEEN_OFFSET + pkmnIndex/8] &= ~mask;
  }
  return true;

}
bool PkmnSaveState::setPkmnPokedexCatched(int pkmnIndex, bool isCatched) {

  pkmnIndex = pkmnIndex - 1;
  int mask = 0x01<<(pkmnIndex % 8);
  if (isCatched) {
    _data[PkmnSaveState::PKMN_POKEDEX_CATCH_OFFSET + pkmnIndex/8] |= mask;
  } else {
    _data[PkmnSaveState::PKMN_POKEDEX_CATCH_OFFSET + pkmnIndex/8] &= ~mask;
  }
  return true;

}
