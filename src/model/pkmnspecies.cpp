#include "pkmnspecies.h"
#include "pkmnelement.h"

#include <algorithm>

PkmnSpecies::PkmnSpecies (int id, int index, string name, byte element1, byte element2) :
  _id(id), _index(index), _name(name), _element1(element1), _element2(element2) { }

PkmnSpecies::PkmnSpecies () : _id(0x1F), _index(0x00), _name("Missingno."),
  _element1(Element::FLYING), _element2(Element::NORMAL) { }

bool PkmnSpecies::isValid() const { return (_index != 0x00); }

int PkmnSpecies::getIndex() const { return _index; }

int PkmnSpecies::getId() const { return _id; }

string PkmnSpecies::getName() const { return _name; }

string PkmnSpecies::getUpperCaseName() const {
  string result = _name;
  std::transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

byte PkmnSpecies::getElement1() const { return _element1; }

byte PkmnSpecies::getElement2() const { return _element2; }

const PkmnSpecies * PkmnSpeciesList::getById(int id) {

  if (id < 1 || id > 190)
    return &_pkmnSpeciesList[0x1F]; // the first" missingno."
  return &_pkmnSpeciesList[id - 1];

}

const PkmnSpecies * PkmnSpeciesList::getByIndex(int index) {

  if (index < 1 || index > 151)
    return &_pkmnSpeciesList[0x1F]; // the first" missingno."
  for (int i = 0; i<190; ++i) {
    if (_pkmnSpeciesList[i].getIndex() == index)
      return &_pkmnSpeciesList[i];
  }
  return &_pkmnSpeciesList[0x1F];
}

const PkmnSpecies* PkmnSpeciesList::getByName(const string &name) {

  for (int i=0; i<190; ++i) {
    if (_pkmnSpeciesList[i].getName() == name)
      return &_pkmnSpeciesList[i];
  }
  return &_pkmnSpeciesList[0x1F];

}

bool comparePkmnOrder(const PkmnSpecies *o1, const PkmnSpecies *o2) {
  return (o1->getIndex() < o2->getIndex());
}

vector<const PkmnSpecies *> PkmnSpeciesList::getByElement(int element) {

  vector<const PkmnSpecies *> result;

  for (int i=0; i<190; ++i) {
    if (_pkmnSpeciesList[i].isValid() &&
        (_pkmnSpeciesList[i].getElement1() == element ||
         _pkmnSpeciesList[i].getElement2() == element))
      result.push_back(&_pkmnSpeciesList[i]);
  }

  std::sort(result.begin(), result.end(), comparePkmnOrder);
  return result;

}

const PkmnSpecies PkmnSpeciesList::_pkmnSpeciesList[] = {
	PkmnSpecies(0x01, 112, "Rhydon"    , Element::GROUND  , Element::ROCK    ),
	PkmnSpecies(0x02, 115, "Kangaskhan", Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x03,  32, "NidoranM"  , Element::POISON  , Element::POISON  ),
	PkmnSpecies(0x04,  35, "Clefairy"  , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x05,  21, "Spearow"   , Element::NORMAL  , Element::FLYING  ),
	PkmnSpecies(0x06, 100, "Voltrob"   , Element::ELECTRIC, Element::ELECTRIC),
	PkmnSpecies(0x07,  34, "Nidoking"  , Element::POISON  , Element::GROUND  ),
	PkmnSpecies(0x08,  80, "Slowbro"   , Element::WATER   , Element::PSYCHIC ),
	PkmnSpecies(0x09,   2, "Ivysaur"   , Element::GRASS   , Element::POISON  ),
	PkmnSpecies(0x0A, 103, "Exeggutor" , Element::GRASS   , Element::PSYCHIC ),
	PkmnSpecies(0x0B, 108, "Lickitung" , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x0C, 102, "Exeggcute" , Element::GRASS   , Element::PSYCHIC ),
	PkmnSpecies(0x0D,  88, "Grimer"    , Element::POISON  , Element::POISON  ),
	PkmnSpecies(0x0E,  94, "Gengar"    , Element::GHOST   , Element::POISON  ),
	PkmnSpecies(0x0F,  29, "NidoranF"  , Element::POISON  , Element::POISON  ),
	PkmnSpecies(0x10,  31, "Nidoqueen" , Element::POISON  , Element::GROUND  ),
	PkmnSpecies(0x11, 104, "Cubone"    , Element::GROUND  , Element::GROUND  ),
	PkmnSpecies(0x12, 111, "Rhyhorn"   , Element::GROUND  , Element::ROCK    ),
	PkmnSpecies(0x13, 131, "Lapras"    , Element::WATER   , Element::ICE     ),
	PkmnSpecies(0x14,  59, "Arcanine"  , Element::FIRE    , Element::FIRE    ),
	PkmnSpecies(0x15, 151, "Mew"       , Element::PSYCHIC , Element::PSYCHIC ),
	PkmnSpecies(0x16, 130, "Gyarados"  , Element::WATER   , Element::FLYING  ),
	PkmnSpecies(0x17,  90, "Shellder"  , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x18,  72, "Tentacool" , Element::WATER   , Element::POISON  ),
  PkmnSpecies(0x19,  92, "Gastly"    , Element::GHOST   , Element::POISON  ),
  PkmnSpecies(0x1A, 123, "Scyther"   , Element::BUG     , Element::FLYING  ),
	PkmnSpecies(0x1B, 120, "Staryu"    , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x1C,   9, "Blastoise" , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x1D, 127, "Pinsir"    , Element::BUG     , Element::BUG     ),
	PkmnSpecies(0x1E, 114, "Tangela"   , Element::GRASS   , Element::GRASS   ),
	PkmnSpecies(0x1F,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x20,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x21,  58, "Growlithe" , Element::FIRE    , Element::FIRE    ),
	PkmnSpecies(0x22,  95, "Onix"      , Element::ROCK    , Element::GROUND  ),
	PkmnSpecies(0x23,  22, "Fearow"    , Element::NORMAL  , Element::FLYING  ),
	PkmnSpecies(0x24,  16, "Pidgey"    , Element::NORMAL  , Element::FLYING  ),
	PkmnSpecies(0x25,  79, "Slowpoke"  , Element::WATER   , Element::PSYCHIC ),
	PkmnSpecies(0x26,  64, "Kadabra"   , Element::PSYCHIC , Element::PSYCHIC ),
	PkmnSpecies(0x27,  75, "Graveler"  , Element::ROCK    , Element::GROUND  ),
	PkmnSpecies(0x28, 113, "Chansey"   , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x29,  67, "Machoke"   , Element::FIGHTING, Element::FIGHTING),
	PkmnSpecies(0x2A, 122, "Mr.Mime"   , Element::PSYCHIC , Element::PSYCHIC ),
	PkmnSpecies(0x2B, 106, "Hitmonlee" , Element::FIGHTING, Element::FIGHTING),
	PkmnSpecies(0x2C, 107, "Hitmonchan", Element::FIGHTING, Element::FIGHTING),
	PkmnSpecies(0x2D,  24, "Arbok"     , Element::POISON  , Element::POISON  ),
	PkmnSpecies(0x2E,  47, "Parasect"  , Element::BUG     , Element::GRASS   ),
	PkmnSpecies(0x2F,  54, "Psyduck"   , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x30,  96, "Drowzee"   , Element::PSYCHIC , Element::PSYCHIC ),
	PkmnSpecies(0x31,  76, "Golem"     , Element::GROUND  , Element::ROCK    ),
	PkmnSpecies(0x32,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x33, 126, "Magmar"    , Element::FIRE    , Element::FIRE    ),
	PkmnSpecies(0x34,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x35, 125, "Electabuzz", Element::ELECTRIC, Element::ELECTRIC),
	PkmnSpecies(0x36,  82, "Magneton"  , Element::ELECTRIC, Element::ELECTRIC),
	PkmnSpecies(0x37, 109, "Koffing"   , Element::POISON  , Element::POISON  ),
	PkmnSpecies(0x38,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x39,  56, "Mankey"    , Element::FIGHTING, Element::FIGHTING),
	PkmnSpecies(0x3A,  86, "Seel"      , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x3B,  50, "Diglett"   , Element::GROUND  , Element::GROUND  ),
	PkmnSpecies(0x3C, 128, "Tauros"    , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x3D,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x3E,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x3F,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x40,  83, "Farfetch'd", Element::NORMAL  , Element::FLYING  ),
	PkmnSpecies(0x41,  48, "Venonat"   , Element::BUG     , Element::POISON  ),
	PkmnSpecies(0x42, 149, "Dragonite" , Element::DRAGON  , Element::FLYING  ),
	PkmnSpecies(0x43,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x44,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x45,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x46,  84, "Doduo"     , Element::NORMAL  , Element::FLYING  ),
	PkmnSpecies(0x47,  60, "Poliwag"   , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x48, 124, "Jynx"      , Element::ICE     , Element::PSYCHIC ),
	PkmnSpecies(0x49, 146, "Moltres"   , Element::FIRE    , Element::FLYING  ),
	PkmnSpecies(0x4A, 144, "Articuno"  , Element::ICE     , Element::FLYING  ),
	PkmnSpecies(0x4B, 145, "Zapdos"    , Element::ELECTRIC, Element::FLYING  ),
	PkmnSpecies(0x4C, 132, "Ditto"     , Element::NORMAL  , Element::NORMAL  ),
  PkmnSpecies(0x4D,  52, "Meowth"    , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x4E,  98, "Krabby"    , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x4F,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x50,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x51,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x52,  37, "Vulpix"    , Element::FIRE    , Element::FIRE    ),
	PkmnSpecies(0x53,  38, "Ninetales" , Element::FIRE    , Element::FIRE    ),
	PkmnSpecies(0x54,  25, "Pikachu"   , Element::ELECTRIC, Element::ELECTRIC),
	PkmnSpecies(0x55,  26, "Raichu"    , Element::ELECTRIC, Element::ELECTRIC),
	PkmnSpecies(0x56,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x57,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x58, 147, "Dratini"   , Element::DRAGON  , Element::DRAGON  ),
	PkmnSpecies(0x59, 148, "Dragonair" , Element::DRAGON  , Element::DRAGON  ),
	PkmnSpecies(0x5A, 140, "Kabuto"    , Element::ROCK    , Element::WATER   ),
	PkmnSpecies(0x5B, 141, "Kabutops"  , Element::ROCK    , Element::WATER   ),
	PkmnSpecies(0x5C, 116, "Horsea"    , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x5D, 117, "Seadra"    , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x5E,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x5F,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x60,  27, "Sandshrew" , Element::GROUND  , Element::GROUND  ),
	PkmnSpecies(0x61,  28, "Sandslash" , Element::GROUND  , Element::GROUND  ),
	PkmnSpecies(0x62, 138, "Omanyte"   , Element::ROCK    , Element::WATER   ),
	PkmnSpecies(0x63, 139, "Omastar"   , Element::ROCK    , Element::WATER   ),
	PkmnSpecies(0x64,  39, "Jigglypuff", Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x65,  40, "Wigglytuff", Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x66, 133, "Eevee"     , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x67, 136, "Flareon"   , Element::FIRE    , Element::FIRE    ),
	PkmnSpecies(0x68, 135, "Jolteon"   , Element::ELECTRIC, Element::ELECTRIC),
	PkmnSpecies(0x69, 134, "Vaporeon"  , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x6A,  66, "Machop"    , Element::FIGHTING, Element::FIGHTING),
	PkmnSpecies(0x6B,  41, "Zubat"     , Element::POISON  , Element::FLYING  ),
	PkmnSpecies(0x6C,  23, "Ekans"     , Element::POISON  , Element::POISON  ),
	PkmnSpecies(0x6D,  46, "Paras"     , Element::BUG     , Element::GRASS   ),
	PkmnSpecies(0x6E,  61, "Poliwhirl" , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x6F,  62, "Poliwrath" , Element::WATER   , Element::FIGHTING),
	PkmnSpecies(0x70,  13, "Weedle"    , Element::BUG     , Element::POISON  ),
	PkmnSpecies(0x71,  14, "Kakuna"    , Element::BUG     , Element::POISON  ),
	PkmnSpecies(0x72,  15, "Beedrill"  , Element::BUG     , Element::POISON  ),
	PkmnSpecies(0x73,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x74,  85, "Dodrio"    , Element::NORMAL  , Element::FLYING  ),
	PkmnSpecies(0x75,  57, "Primeape"  , Element::FIGHTING, Element::FIGHTING),
	PkmnSpecies(0x76,  51, "Dugtrio"   , Element::GROUND  , Element::GROUND  ),
	PkmnSpecies(0x77,  49, "Venomoth"  , Element::BUG     , Element::POISON  ),
	PkmnSpecies(0x78,  87, "Dewgong"   , Element::WATER   , Element::ICE     ),
	PkmnSpecies(0x79,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x7A,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x7B,  10, "Caterpie"  , Element::BUG     , Element::BUG     ),
	PkmnSpecies(0x7C,  11, "Metapod"   , Element::BUG     , Element::BUG     ),
	PkmnSpecies(0x7D,  12, "Butterfree", Element::BUG     , Element::FLYING  ),
	PkmnSpecies(0x7E,  68, "Machamp"   , Element::FIGHTING, Element::FIGHTING),
	PkmnSpecies(0x7F,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x80,  55, "Golduck"   , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x81,  97, "Hypno"     , Element::PSYCHIC , Element::PSYCHIC ),
	PkmnSpecies(0x82,  42, "Golbat"    , Element::POISON  , Element::FLYING  ),
  PkmnSpecies(0x83, 150, "Mewtwo"    , Element::PSYCHIC , Element::PSYCHIC ),
	PkmnSpecies(0x84, 143, "Snorlax"   , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x85, 129, "Magikarp"  , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x86,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x87,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x88,  89, "Muk"       , Element::POISON  , Element::POISON  ),
	PkmnSpecies(0x89,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x8A,  99, "Kingler"   , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x8B,  91, "Cloyster"  , Element::WATER   , Element::ICE     ),
	PkmnSpecies(0x8C,  00, "Missingno.", Element::FIGHTING, Element::FIGHTING),
	PkmnSpecies(0x8D, 101, "Electrode" , Element::ELECTRIC, Element::ELECTRIC),
	PkmnSpecies(0x8E,  36, "Clefable"  , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x8F, 110, "Weezing"   , Element::POISON  , Element::POISON  ),
	PkmnSpecies(0x90,  53, "Persian"   , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0x91, 105, "Marowak"   , Element::GROUND  , Element::GROUND  ),
	PkmnSpecies(0x92,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x93,  93, "Haunter"   , Element::GHOST   , Element::POISON  ),
	PkmnSpecies(0x94,  63, "Abra"      , Element::PSYCHIC , Element::PSYCHIC ),
	PkmnSpecies(0x95,  65, "Alakazam"  , Element::PSYCHIC , Element::PSYCHIC ),
	PkmnSpecies(0x96,  17, "Pidgeotto" , Element::NORMAL  , Element::FLYING  ),
	PkmnSpecies(0x97,  18, "Pidgeot"   , Element::NORMAL  , Element::FLYING  ),
	PkmnSpecies(0x98, 121, "Starmie"   , Element::WATER   , Element::PSYCHIC ),
	PkmnSpecies(0x99,   1, "Bulbasaur" , Element::GRASS   , Element::POISON  ),
	PkmnSpecies(0x9A,   3, "Venusaur"  , Element::GRASS   , Element::POISON  ),
	PkmnSpecies(0x9B,  73, "Tentacruel", Element::WATER   , Element::POISON  ),
	PkmnSpecies(0x9C,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0x9D, 118, "Goldeen"   , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x9E, 119, "Seaking"   , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0x9F,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xA0,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xA1,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xA2,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xA3,  77, "Ponyta"    , Element::FIRE    , Element::FIRE    ),
	PkmnSpecies(0xA4,  78, "Rapidash"  , Element::FIRE    , Element::FIRE    ),
	PkmnSpecies(0xA5,  19, "Rattata"   , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0xA6,  20, "Raticate"  , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0xA7,  33, "Nidorino"  , Element::POISON  , Element::POISON  ),
	PkmnSpecies(0xA8,  30, "Nidorina"  , Element::POISON  , Element::POISON  ),
	PkmnSpecies(0xA9,  74, "Geodude"   , Element::ROCK    , Element::GROUND  ),
	PkmnSpecies(0xAA, 137, "Porygon"   , Element::NORMAL  , Element::NORMAL  ),
	PkmnSpecies(0xAB, 142, "Aerodactyl", Element::ROCK    , Element::FLYING  ),
	PkmnSpecies(0xAC,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xAD,  81, "Magnemite" , Element::ELECTRIC, Element::ELECTRIC),
	PkmnSpecies(0xAE,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xAF,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xB0,   4, "Charmander", Element::FIRE    , Element::FIRE    ),
	PkmnSpecies(0xB1,   7, "Squirtle"  , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0xB2,   5, "Charmeleon", Element::FIRE    , Element::FIRE    ),
	PkmnSpecies(0xB3,   8, "Wartortle" , Element::WATER   , Element::WATER   ),
	PkmnSpecies(0xB4,   6, "Charizard" , Element::FIRE    , Element::FLYING  ),
	PkmnSpecies(0xB5,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xB6,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xB7,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xB8,  00, "Missingno.", Element::FLYING  , Element::NORMAL  ),
	PkmnSpecies(0xB9,  43, "Oddish"    , Element::GRASS   , Element::POISON  ),
	PkmnSpecies(0xBA,  44, "Gloom"     , Element::GRASS   , Element::POISON  ),
	PkmnSpecies(0xBB,  45, "Vileplume" , Element::GRASS   , Element::POISON  ),
	PkmnSpecies(0xBC,  69, "Bellsprout", Element::GRASS   , Element::POISON  ),
	PkmnSpecies(0xBD,  70, "Weepinbell", Element::GRASS   , Element::POISON  ),
	PkmnSpecies(0xBE,  71, "Victreebel", Element::GRASS   , Element::POISON  )};
