#ifndef PKMN_OFFSET_MANAGER
#define PKMN_OFFSET_MANAGER

#include "pkmndataformat.h"

class PkmnOffsetManager {

public:

  static int getPartyPkmnCountOffset();
  static int getPartyPkmnListOffset(int);
  static int getPartyPkmnParameterOffset(int, int);

  static int getCurrentBoxNumberOffset();
  static int getBoxPkmnCountOffset(int, int);
  static int getBoxPkmnListOffset(int, int, int);
  static int getBoxPkmnParameterOffset(int, int, int, int);

  static int getOriginalTrainerNameOffset();
  static int getOriginalTrainerIdOffset();
  static int getNemesisTrainerNameOffset();
  static int getMoneyOffset();
  static int getChecksumOffset();


private:

  enum StoreOffset {
    PKMNCOUNTDATA,
    PKMNSPECIESLISTDATA,
    PKMNSTATSDATA,
    PKMNOTNAMEDATA,
    PKMNNAMEDATA
  };
  static int getPartyDataOffset(int);
  static int getBoxDataOffset(int);

  static const int ORIGINAL_TRAINER_NAME_OFFSET = 0x2598;
  static const int ORIGINAL_TRAINER_ID_OFFSET   = 0x2605;
  static const int NEMESIS_TRAINER_NAME_OFFSET  = 0x25F6;
  static const int MONEY_OFFSET                 = 0x25F3;
  //static const int BADGES_OFFSET                = 0x0000;

  static const int POKEDEX_PKMN_CATCH_OFFSET    = 0x25A3;
  static const int POKEDEX_PKMN_SEEN_OFFSET     = 0x25B6;

  static const int PARTY_START_OFFSET           = 0x2F2C;

  static const int CURRENT_BOX_NUMBER_OFFSET    = 0x284C;
  static const int CURRENT_BOX_START_OFFSET     = 0x30C0;
  static const int STORED_BOX_START_OFFSET1     = 0x4000;
  static const int STORED_BOX_START_OFFSET2     = 0x6000;
  //static const int STORED_BOX_START_OFFSET     = 0x4462;

  /*
  // party
  static const uint PARTY_PKMN_COUNT_OFFSET      = 0x2F2C;
  static const uint PARTY_PKMN_SPECIES_OFFSET    = 0x2F2D;
  static const uint PARTY_PKMN_STATE_OFFSET      = 0x2F34;
  static const uint PARTY_PKMN_NAMES_OFFSET      = 0x307E;
  static const uint PARTY_PKMN_OT_NAME_OFFSET    = 0x303C;
  // current box
  static const uint CURRENT_BOX_PKMN_COUNT_OFFSET    = 0x30C0;
  static const uint CURRENT_BOX_PKMN_SPECIES_OFFSET   = 0x30C1;
  static const uint CURRENT_BOX_PKMN_STATE_OFFSET     = 0x30D6;
  static const uint CURRENT_BOX_PKMN_OT_NAME_OFFSET   = 0x336A;
  static const uint CURRENT_BOX_PKMN_NAME_OFFSET      = 0x3446;
  // non current box
  static const uint BOX_PKMN_COUNT_OFFSET    = 0x4462;
  static const uint BOX_PKMN_SPECIES_OFFSET   = 0x4463;
  static const uint BOX_PKMN_STATE_OFFSET     = 0x4478;
  static const uint BOX_PKMN_OT_NAME_OFFSET   = 0x470C;
  static const uint BOX_PKMN_NAME_OFFSET      = 0x47E8;
  */

  static const int CHECKSUM_OFFSET              = 0x3523;

};

#endif // PKMN_OFFSET_MANAGER
