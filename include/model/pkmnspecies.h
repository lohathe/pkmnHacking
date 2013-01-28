#ifndef PKMN_SPECIES
#define PKMN_SPECIES

#include "pkmndataformat.h"

#include <string>
using std::string;
#include <vector>
using std::vector;

class PkmnSpecies {

public:

  PkmnSpecies ();
  PkmnSpecies (int, int, string, byte, byte);

  bool isValid() const;
  int getIndex() const;
  int getId() const;
  string getName() const;
  byte getElement1() const;
  byte getElement2() const;

private:

  int _id, _index;
  string _name;
  byte _element1, _element2;

};

class PkmnSpeciesList {

public:

  static const int INDEX    = 0x01;
  static const int ID       = 0x02;
  static const int ELEMENT  = 0x03;

  static const PkmnSpecies * get (int);
  static const PkmnSpecies * get (const string &);
  static vector<const PkmnSpecies *> getBy(int, int);

private:

  static const PkmnSpecies _pkmnSpeciesList[190];

};

#endif // PKMN_SPECIES
