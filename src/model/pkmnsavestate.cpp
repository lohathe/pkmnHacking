#include "pkmnsavestate.h"

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

void PkmnSaveState::saveToFile() const {

  _data[PkmnSaveState::CHECKSUM_OFFSET] = checksum();

  std::ofstream outputFile (_filepath.c_str(), std::ios::binary | std::ios::trunc);
  
  outputFile.seekp(0, std::ios::beg);
  outputFile.write(reinterpret_cast<char *>(_data), _dataLength);
  outputFile.close();

}

vector<const PkmnSpecies *> PkmnSaveState::getPartyPkmn() const {

  vector<const PkmnSpecies *> result;
  
  for (int i=0; i<6; ++i) {
    const PkmnSpecies *activePkmn = 
      PkmnSpeciesList::get(_data[PkmnSaveState::BELT_PKMN_SPCS_OFFSET + i]);
    result.push_back(activePkmn);
  }
  
  return result;

}

int PkmnSaveState::getPartyPkmnCount() const {

  return static_cast<int>(_data[PkmnSaveState::BELT_PKMN_NMBR_OFFSET]);

}

int PkmnSaveState::getTrainerId() const {
  return static_cast<int>((_data[PkmnSaveState::TRAINER_OFFSET]<<8) + 
                          (_data[PkmnSaveState::TRAINER_OFFSET + 1]&0xFF));
}

// number in [1 .. 6]
PkmnState* PkmnSaveState::getPkmnState(int index) const {

  if (!pkmnExistsAtIndex(index))
    return NULL;

  return new PkmnState(
    &( _data[PkmnSaveState::PKMN_STATE_OFFSET + 44*(index-1)] ),
    &( _data[PkmnSaveState::PKMN_NAMES_OFFSET + 11*(index-1)] ),
    index);

}

void PkmnSaveState::setPkmnState(PkmnState *pkmnvalue) {

  int beltOffset  = PkmnSaveState::BELT_PKMN_SPCS_OFFSET + 
                    (pkmnvalue->getPartyIndex() - 1);
  int stateOffset = PkmnSaveState::PKMN_STATE_OFFSET +
                    (pkmnvalue->getPartyIndex() - 1)*44;
  int nameOffset  = PkmnSaveState::PKMN_NAMES_OFFSET +
                    (pkmnvalue->getPartyIndex() - 1)*11;
                    
  // set the belt information
  _data[beltOffset] = static_cast<byte>(pkmnvalue->get(SPECIES));
  
  // set pkmn state data information
  for (int i = 0; i < 44; ++i)
    _data[stateOffset + i] = pkmnvalue->getUnformattedData()[i];

  // set pkmn name data information
  for (int i = 0; i < 11; ++i)
    _data[nameOffset + i] = pkmnvalue->getUnformattedName()[i];

}

// number in [1 .. 6]
bool PkmnSaveState::createPkmnStateAtIndex(int index) {

  // can create pokemon only if the previous (number-1) exist
  for (int i=1; i<index; i++)
    if (!pkmnExistsAtIndex(i))
      return false;
  if (pkmnExistsAtIndex(index)) 
    return false;

  // :: reserve room in the 'party area' ::
  // increase pkmn number in party
  _data[PkmnSaveState::BELT_PKMN_NMBR_OFFSET] =
    static_cast<byte>(_data[PkmnSaveState::BELT_PKMN_NMBR_OFFSET] + 1);
  // shifting pkmn information in party
  _data[PkmnSaveState::BELT_PKMN_SPCS_OFFSET + index - 1] =
    static_cast<byte>(0x01);
  _data[PkmnSaveState::BELT_PKMN_SPCS_OFFSET + index] =
    static_cast<byte>(0xFF);
  
  return true;

}

// number in [1 .. 6]
bool PkmnSaveState::deletePkmnStateAtIndex(int index) {

  if (!pkmnExistsAtIndex(index))
    return false;
  // cannot delete last pokemon
  if (_data[PkmnSaveState::BELT_PKMN_NMBR_OFFSET] == 1)
    return false;

  // :: decrease pkmn number in party
  _data[PkmnSaveState::BELT_PKMN_NMBR_OFFSET] =
    static_cast<byte>(_data[PkmnSaveState::BELT_PKMN_NMBR_OFFSET] - 1);
    
  // :: shifting pkmn information to fill cleared data locations
  for (int i=index-1; i<6; ++i) {
  
    // shifting 'party area'
    _data[PkmnSaveState::BELT_PKMN_SPCS_OFFSET + i] =
      _data[PkmnSaveState::BELT_PKMN_SPCS_OFFSET + i + 1];
    
    if (i<5) {
      // shifting 'stats area'
      for (int j=0; j<44; ++j)
        _data[PkmnSaveState::PKMN_STATE_OFFSET + i*44 + j] =
          _data[PkmnSaveState::PKMN_STATE_OFFSET + (i+1)*44 + j];
    
      // shifting 'names area'
      for (int j=0; j<11; ++j)
        _data[PkmnSaveState::PKMN_NAMES_OFFSET + i*11 + j] =
          _data[PkmnSaveState::PKMN_NAMES_OFFSET + (i+1)*11 + j];
    }
  }
  
  // :: deleting last memory location
  _data[PkmnSaveState::BELT_PKMN_SPCS_OFFSET + 6] = static_cast<byte>(0x00);
  for (int j=0; j<44; ++j)
    _data[PkmnSaveState::PKMN_STATE_OFFSET + 5*44 + j] = static_cast<byte>(0x00);
  for (int j=0; j<11; ++j)
    _data[PkmnSaveState::PKMN_NAMES_OFFSET + 5*11 + j] = static_cast<byte>(0x00);

  return true;

}

byte PkmnSaveState::checksum () const {

  byte t = 0x00;
  for (int i= 0x2598; i<0x3523; i++) {
    t = static_cast<byte>(t + _data[i]);
  }
  
  return static_cast<byte>(t ^ 0xFF);
}


//  index in [1 .. 6]
bool PkmnSaveState::pkmnExistsAtIndex (int index) const {

  if (index < 1 || index > 6) 
    return false;

  if (_data[PkmnSaveState::BELT_PKMN_SPCS_OFFSET + index - 1] == 0xFF )
//      || _data[PkmnSaveState::BELT_PKMN_SPCS_OFFSET + index - 1] == 0x00 )
    return false;
  return true;

}
