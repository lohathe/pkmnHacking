#ifndef PKMN_ALIMENT
#define PKMN_ALIMENT

#include "pkmndataformat.h"

#include <string>
using std::string;

class Aliment {

public:

  static const byte OK        = 0x00;
  static const byte ASLEEP    = 0x04;
  static const byte POISONED  = 0x08;
  static const byte BURNED    = 0x10;
  static const byte FROZEN    = 0x20;
  static const byte PARALYZED = 0x40;
  
  static string toString (const byte aliment) {
    switch (aliment) {
      case Aliment::OK        : return "ok";
      case Aliment::ASLEEP    : return "asleep";
      case Aliment::POISONED  : return "poisoned";
      case Aliment::BURNED    : return "burned";
      case Aliment::FROZEN    : return "frozen";
      case Aliment::PARALYZED : return "paralyzed";
    }
    return "error";
  }

};

#endif // PKMN_ALIMENT
