#include "pkmnstate.h"
#include "pkmnstringreader.h"

PkmnState::PkmnState(const byte *data, const byte *name)
  : _data(data), _name(name) {}

bool PkmnState::isValid() const {

  return (_data != NULL) && (_name != NULL);

}

int PkmnState::getMinValue (int info) {
  int result = 0;
  if (info & (SPECIES)) result = 0x01;
  else if (info & (IV)) result = 0x00;
  else if (info & (HP | MAXHP | ATT | DEF | SPD | SPC)) result = 0x01;
  else if (info & (LEVEL | LEVELN)) result = 0x01;
  else if (info & (ALIMENT)) result = 0x00;
  else if (info & (TYPE1 | TYPE2)) result = 0x00;
  else if (info & (MOVE1 | MOVE2 | MOVE3 | MOVE4)) result = 0x00;
  else if (info & (MOVE1PP | MOVE2PP | MOVE3PP | MOVE4PP)) result = 0x00;
  else if (info & (EXP)) result = 0x01;
  else if (info & (TRAINER)) result = 0x00;
  else if (info & (HPEV | ATTEV | DEFEV | SPDEV | SPCEV)) result = 0x00;
  return result;
}
int PkmnState::getMaxValue (int info) {
  int result = 0xFF;
  if (info & (SPECIES)) result = 0xBE;
  else if (info & (HP | MAXHP | ATT | DEF | SPD | SPC)) result = 0xFFFF;
  else if (info & (LEVEL | LEVELN)) result = 0x63;
  else if (info & (ALIMENT)) result = 0x40;
  else if (info & (TYPE1 | TYPE2)) result = 0x1A;
  else if (info & (MOVE1 | MOVE2 | MOVE3 | MOVE4)) result = 0xA5;
  else if (info & (MOVE1PP | MOVE2PP | MOVE3PP | MOVE4PP)) result = 0xFF;
  else if (info & (EXP)) result = 0xFFFFFF;
  else if (info & (TRAINER)) result = 0xFFFF;
  else if (info & (HPEV | ATTEV | DEFEV | SPDEV | SPCEV | IV)) result = 0xFFFF;
  return result;
}
int PkmnState::getOffset (int info) {
  switch (info) {
    case SPECIES   : return 0x00;
    case HP        : return 0x01;
    case LEVELN    : return 0x03;
    case ALIMENT   : return 0x04;
    case TYPE1     : return 0x05;
    case TYPE2     : return 0x06;
    case CATCHRATE : return 0x07;
    case MOVE1     : return 0x08;
    case MOVE2     : return 0x09;
    case MOVE3     : return 0x0A;
    case MOVE4     : return 0x0B;
    case TRAINER   : return 0x0C;
    case EXP       : return 0x0E;
    case HPEV      : return 0x11;
    case ATTEV     : return 0x13;
    case DEFEV     : return 0x15;
    case SPDEV     : return 0x17;
    case SPCEV     : return 0x19;
    case IV        : return 0x1B;
    case MOVE1PP   : return 0x1D;
    case MOVE2PP   : return 0x1E;
    case MOVE3PP   : return 0x1F;
    case MOVE4PP   : return 0x20;
    case LEVEL     : return 0x21;
    case MAXHP     : return 0x22;
    case ATT       : return 0x24;
    case DEF       : return 0x26;
    case SPD       : return 0x28;
    case SPC       : return 0x2A;
  }
  return 0x00;
}
int PkmnState::getInfoSize (int info) {
  int twobyteinfo = HP | TRAINER | HPEV | ATTEV | DEFEV | SPDEV | SPCEV |
                    IV | MAXHP | ATT | DEF | SPD | SPC;
  int threebyteinfo = EXP;
  if ( (info & twobyteinfo) != 0   ) return 2;
  if ( (info & threebyteinfo) != 0 ) return 3;
  return 1;
}

int PkmnState::get (int info) const {

  int result = 0;
  int startingOffset = PkmnState::getOffset(info);
  for (int i=0; i<PkmnState::getInfoSize(info); i++) {
    result = (result*256) + (static_cast<int>(_data[startingOffset + i]) & 0xFF);
  }
  return result;
}

string PkmnState::getName() const {
  return PkmnStringReader::toStdString(_name);
}

