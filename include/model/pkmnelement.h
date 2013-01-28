#ifndef PKMN_ELEMENT
#define PKMN_ELEMENT

#include "pkmndataformat.h"

#include <string>
using std::string;

class Element {

public:

  static const byte NORMAL   = 0x00;
  static const byte FIGHTING = 0x01;
  static const byte FLYING   = 0x02;
  static const byte POISON   = 0x03;
  static const byte GROUND   = 0x04;
  static const byte ROCK     = 0x05;
  static const byte BUG      = 0x07;
  static const byte GHOST    = 0x08;
  static const byte FIRE     = 0x14;
  static const byte WATER    = 0x15;
  static const byte GRASS    = 0x16;
  static const byte ELECTRIC = 0x17;
  static const byte PSYCHIC  = 0x18;
  static const byte ICE      = 0x19;
  static const byte DRAGON   = 0x1A;

  static string toString(const byte element) {
    switch(element) {
      case Element::NORMAL   : return "normal";
      case Element::FIGHTING : return "fighting";
      case Element::FLYING   : return "flying";
      case Element::POISON   : return "poison";
      case Element::GROUND   : return "ground";
      case Element::ROCK     : return "rock";
      case Element::BUG      : return "bug";
      case Element::GHOST    : return "ghost";
      case Element::FIRE     : return "fire";
      case Element::WATER    : return "water";
      case Element::GRASS    : return "grass";
      case Element::ELECTRIC : return "electric";
      case Element::PSYCHIC  : return "psychic";
      case Element::ICE      : return "ice";
      case Element::DRAGON   : return "dragon";
    }
    return "no element";
  }

};

#endif // PKMN_ELEMENT