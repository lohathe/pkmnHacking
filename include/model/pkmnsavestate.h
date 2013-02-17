#ifndef PKMN_SAVE_STATE
#define PKMN_SAVE_STATE

#include "pkmndataformat.h"
#include "pkmnstate.h"
#include "pkmnpokedex.h"
#include "pkmnspecies.h"

#include <string>
using std::string;
#include <vector>
using std::vector;

class PkmnSaveState {

public:

  PkmnSaveState (string, bool backup = false);

  // GENERAL INFO
  bool saveToFile() const;
  bool openFile(const string &);

  int getTrainerId() const;

  // PARTY PKMN INFO
  vector<const PkmnSpecies *> getPartyPkmnList() const;
  int getPartyPkmnCount() const;

  int getPartyPkmnParameter(int, int) const;
  string getPartyPkmnName(int) const;
  PkmnState getPartyPkmnState(int) const;
  bool setPartyPkmnParameter(int, int, int);
  bool setPartyPkmnStrParam(int, int, string);

  bool createPartyPkmnAtIndex(int, int);
  bool deletePartyPkmnAtIndex(int);
  
  // POKEDEX PKMN INFO
  PkmnPokedex getPkmnPokedex() const;
  bool setPkmnPokedexSeen(int, bool);
  bool setPkmnPokedexCatched(int, bool);

private:

  string _filepath;
  byte *_data;
  int _dataLength;
  bool _backup;
/*
  static const int ORIGINAL_TRAINER_NAME_OFFSET = 0x2590;
  static const int ORIGINAL_TRAINER_ID_OFFSET   = 0x2605;
  static const int NEMESIS_TRAINER_NAME_OFFSET  = 0x25F6;
  static const int MONEY_OFFSET                 = 0x25F3;
  //static const int BADGES_OFFSET                = 0x0000;
*/
  static const int POKEDEX_PKMN_CATCH_OFFSET    = 0x25A3;
  static const int POKEDEX_PKMN_SEEN_OFFSET     = 0x25B6;
/*
  static const int PARTY_PKMN_COUNT_OFFSET      = 0x2F2C;
  static const int PARTY_PKMN_SPECIES_OFFSET    = 0x2F2D;
  static const int PARTY_PKMN_STATE_OFFSET      = 0x2F34;
  static const int PARTY_PKMN_NAMES_OFFSET      = 0x307E;
  static const int PARTY_PKMN_OT_NAME_OFFSET    = 0x303C;

  static const int CURRENT_BOX_NUMBER = 0x284C;
  // current box
  static const int CURRENT_BOX_PKMN_COUNT_OFFSET1    = 0x30C0;
  static const int CURRENT_BOX_PKMN_SPECIES_OFFSET   = 0x30C1;
  static const int CURRENT_BOX_PKMN_STATE_OFFSET     = 0x30D6;
  static const int CURRENT_BOX_PKMN_OT_NAME_OFFSET   = 0x336A;
  static const int CURRENT_BOX_PKMN_NAME_OFFSET      = 0x3446;
  // non current box
  static const int BOX_PKMN_COUNT_OFFSET1    = 0x4462;
  static const int BOX_PKMN_SPECIES_OFFSET   = 0x4463;
  static const int BOX_PKMN_STATE_OFFSET     = 0x4478;
  static const int BOX_PKMN_OT_NAME_OFFSET   = 0x470C;
  static const int BOX_PKMN_NAME_OFFSET      = 0x47E8;

  static const int CHECKSUM_OFFSET              = 0x3523;
*/
  byte checksum () const;
  bool pkmnExistsAtPartyIndex (int) const;
  int readData(int, int) const;

};

#endif // PKMN_SAVE_STATE

/*
  CHECKSUM BYTE      : 0x3523
  PKMN STATE OFFSET  : 0x2F34 [44 byte x6]
  PKMN TRAINER NAME  : 0x303C [11 byte x6] (party pkmn)
  PKMN NAME OFFSET   : 0x307E [11 byte x6] (party pkmn)
  PKMN NUMBER        : 0x2f2c [1 byte]
  PKMN READY         : 0x2f2d [7 byte (last byte is FF)]
  
  
  MONEY              : 0x25f3 [3 byte. not in hex,but decimal!]
*/
