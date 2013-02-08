#ifndef PKMN_POKEDEX
#define PKMN_POKEDEX

#include "pkmndataformat.h"

enum PkmnPokedexStatus{
  UNKNOWN = 0x00,
  SEEN    = 0x01,
  CATCHED = 0x02};

class PkmnPokedex {

public:

  PkmnPokedex (byte *, byte *);

  bool isPkmnSeen(int) const;
  bool isPkmnCatched(int) const;

private:

  byte *_seen;
  byte *_catched;

};

#endif // PKMN_POKEDEX
