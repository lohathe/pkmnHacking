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
  string getUpperCaseName() const;
  byte getElement1() const;
  byte getElement2() const;

private:

  int _id, _index;
  string _name;
  byte _element1, _element2;

};

class PkmnSpeciesList {

public:

  static const PkmnSpecies * getById (int);
  static const PkmnSpecies * getByIndex (int);
  static const PkmnSpecies * getByName (const string &);
  static vector<const PkmnSpecies *> getByElement(int);

private:

  static const PkmnSpecies _pkmnSpeciesList[190];

};

#endif // PKMN_SPECIES
