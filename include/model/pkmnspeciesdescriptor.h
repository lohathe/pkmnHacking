#ifndef PKMN_SPECIES_DESCRIPTOR
#define PKMN_SPECIES_DESCRIPTOR

#include "pkmndataformat.h"

#include <string>
using std::string;
#include <vector>
using std::vector;

class MoveLevel {

public:

  MoveLevel (int, int);
  int getLevel() const;
  int getMove() const;

private:
  int _level, _move;

};

class PkmnSpeciesDescriptor {

public:

  PkmnSpeciesDescriptor(int, int, int, int, int, int, int, int, int, vector<MoveLevel>);

  static const int TRANSFER = -1;
  static const int FIRESTONE = -2;
  static const int LEAFSTONE = -3;
  static const int WATERSTONE = -4;
  static const int THUNDERSTONE = -5;
  static const int MOONSTONE = -6;

private:

  int _pkmnIndex;
  //string _pkmnPokedexDescription;
  int _pkmnEvolveFrom;
  int _pkmnEvolutionMethod;
  int _levelingSpeed;
  int _basicHp;
  int _basicAtt;
  int _basicDef;
  int _basicSpd;
  int _basicSpc;
  vector<MoveLevel> _learningSet;


};

#endif // PKMN_SPECIES_DESCRIPTOR
