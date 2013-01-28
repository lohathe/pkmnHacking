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

  vector<const PkmnSpecies *> getPartyPkmn() const;
  int getPartyPkmnCount() const;
  int getTrainerId() const;

  PkmnState* getPkmnState(int) const;
  void setPkmnState(PkmnState*);

  bool createPkmnStateAtIndex(int);
  bool deletePkmnStateAtIndex(int);
  
  void saveToFile() const;


private:

  string _filepath;
  byte *_data;
  int _dataLength;

  static const int TRAINER_OFFSET        = 0x2605;
  static const int BELT_PKMN_NMBR_OFFSET = 0x2F2C;
  static const int BELT_PKMN_SPCS_OFFSET = 0x2F2D;
  static const int PKMN_STATE_OFFSET     = 0x2F34;
  static const int PKMN_NAMES_OFFSET     = 0x307E;
  static const int CHECKSUM_OFFSET       = 0x3523;

  byte checksum () const;
  bool pkmnExistsAtIndex (int) const;

};

#endif // PKMN_SAVE_STATE

/*
  CHECKSUM BYTE      : 0x3523
  PKMN STATE OFFSET  : 0x2F34 [44 byte x6]
  PKMN NAME OFFSET   : 0x307E [11 byte x6]
  PKMN NUMBER        : 0x2f2c [1 byte]
  PKMN READY         : 0x2f2d [7 byte (last byte is FF)]
*/
