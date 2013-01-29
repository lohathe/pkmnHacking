#ifndef PKMN_SAVE_STATE
#define PKMN_SAVE_STATE

#include "pkmndataformat.h"
#include "pkmnstate.h"
#include "pkmnspecies.h"

#include <string>
using std::string;
#include <vector>
using std::vector;

class PkmnSaveState {

public:

  PkmnSaveState (string, bool backup = false);

  // GENERAL INFO
  int getTrainerId() const;

  // PARTY PKMN INFO
  vector<const PkmnSpecies *> getPartyPkmnList() const;
  int getPartyPkmnCount() const;

  int getPartyPkmnParameter(int, int) const;
  string getPartyPkmnName(int) const;
  PkmnState* getPartyPkmnState(int) const;
  bool setPartyPkmnParameter(int, int, int);
  bool setPartyPkmnName(int, string);

  bool createPartyPkmnAtIndex(int, int);
  bool deletePartyPkmnAtIndex(int);
  
  bool saveToFile() const;


private:

  string _filepath;
  byte *_data;
  int _dataLength;

  static const int TRAINER_OFFSET            = 0x2605;
  static const int PARTY_PKMN_COUNT_OFFSET   = 0x2F2C;
  static const int PARTY_PKMN_SPECIES_OFFSET = 0x2F2D;
  static const int PARTY_PKMN_STATE_OFFSET   = 0x2F34;
  static const int PARTY_PKMN_NAMES_OFFSET   = 0x307E;
  static const int CHECKSUM_OFFSET           = 0x3523;

  byte checksum () const;
  bool pkmnExistsAtPartyIndex (int) const;

};

#endif // PKMN_SAVE_STATE

/*
  CHECKSUM BYTE      : 0x3523
  PKMN STATE OFFSET  : 0x2F34 [44 byte x6]
  PKMN NAME OFFSET   : 0x307E [11 byte x6]
  PKMN NUMBER        : 0x2f2c [1 byte]
  PKMN READY         : 0x2f2d [7 byte (last byte is FF)]
*/
