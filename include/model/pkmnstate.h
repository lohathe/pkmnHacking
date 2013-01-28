#ifndef PKMN_STATE
#define PKMN_STATE

#include <string>
using std::string;
#include "pkmndataformat.h"

enum PkmnStateInfo {
  SPECIES   = 0x00000001,
  HP        = 0x00000002,
  LEVELN    = 0x00000004,
  ALIMENT   = 0x00000008,
  TYPE1     = 0x00000010,
  TYPE2     = 0x00000020,
  CATCHRATE = 0x00000040,
  MOVE1     = 0x00000080,
  MOVE2     = 0x00000100,
  MOVE3     = 0x00000200,
  MOVE4     = 0x00000400,
  TRAINER   = 0x00000800,
  EXP       = 0x00001000,
  HPEV      = 0x00002000,
  ATTEV     = 0x00004000,
  DEFEV     = 0x00008000,
  SPDEV     = 0x00010000,
  SPCEV     = 0x00020000,
  IV        = 0x00040000,
  MOVE1PP   = 0x00080000,
  MOVE2PP   = 0x00100000,
  MOVE3PP   = 0x00200000,
  MOVE4PP   = 0x00400000,
  LEVEL     = 0x00800000,
  MAXHP     = 0x01000000,
  ATT       = 0x02000000,
  DEF       = 0x04000000,
  SPD       = 0x08000000,
  SPC       = 0x10000000
};

class PkmnState {

public:

  PkmnState(const byte*, const byte*, int);
  void setDefaultParameters();

  int get(int) const;
  void set(int, int);

  static int getMinValue (int);
  static int getMaxValue (int);
  
  string getName() const;
  void setName(const string &);
  
  const byte* getUnformattedData() const;
  const byte* getUnformattedName() const;
  int getPartyIndex() const;

  bool isValid() const;

private:

  byte _data[44];
  byte _name[11];
  int _partyIndex;
  
  static int getOffset   (int);
  static int getInfoSize (int);

};

#endif // PKMN_STATE
