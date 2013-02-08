#include "pkmnpokedex.h"

PkmnPokedex::PkmnPokedex (byte *seen, byte *catched) :
  _seen(seen), _catched(catched) { }

bool PkmnPokedex::isPkmnSeen(int pkmnIndex) const {

  pkmnIndex = pkmnIndex - 1;
  int mask = 0x01<<(pkmnIndex%8);
  return _seen[pkmnIndex/8] & mask;

}
bool PkmnPokedex::isPkmnCatched(int pkmnIndex) const {

  pkmnIndex = pkmnIndex - 1;
  int mask = 0x01<<(pkmnIndex%8);
  return _catched[pkmnIndex/8] & mask;

}

