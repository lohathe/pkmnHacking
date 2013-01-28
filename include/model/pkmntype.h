#ifndef PKMN_TYPE
#define PKMN_TYPE

#include "pkmndataformat.h"

#include <string>
using std::string;

class Type {

public:

  static const byte PHYSICAL = 0x01;
  static const byte SPECIAL  = 0x02;
  static const byte STATUS   = 0x04;
  
  static string toString (const byte type) {
    string result;
    switch (type) {
      case Type::PHYSICAL: 
        result = "physical";
        break;
      case Type::SPECIAL:
        result = "special";
        break;
      case Type::STATUS: 
        result = "status";
        break;
      default:
        result = "notype";
    }
    return result;
  }
};

#endif // PKMN_TYPE
