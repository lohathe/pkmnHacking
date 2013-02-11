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

  PkmnSpeciesDescriptor(int, int, int, int, int, int, int, int, vector<MoveLevel>);

  static const int TRADE = -1;
  static const int FIRESTONE = -2;
  static const int WATERSTONE = -3;
  static const int THUNDERSTONE = -4;
  static const int LEAFSTONE = -5;
  static const int MOONSTONE = -6;

  static const int FAST = 1;
  static const int MEDIUMFAST = 2;
  static const int MEDIUMSLOW = 3;
  static const int SLOW = 4;

  int getIndex() const;
  int getEvMethod() const;
  string getEvMethodString() const;
  int getLvlSpeed() const;
  int getBasicHP() const;
  int getBasicAtt() const;
  int getBasicDef() const;
  int getBasicSpd() const;
  int getBasicSpc() const;
  vector<MoveLevel> getLearningSet() const;
  vector<int> getNextEvolutions() const;
  vector<int> getPrevEvolutions() const;

private:

  int _pkmnIndex;
  int _pkmnEvolutionMethod;
  int _levelingSpeed;
  int _basicHp;
  int _basicAtt;
  int _basicDef;
  int _basicSpd;
  int _basicSpc;
  vector<MoveLevel> _learningSet;


};

class PkmnSpeciesDescriptorList {

public:

  static const PkmnSpeciesDescriptor *get(int);
  static void print(int, int);

private:

  // _pkmnList[0] == missingno
  // _pkmnList[i] == i-th pkmn (by index)
  static PkmnSpeciesDescriptor* _pkmnList[152];

  static void initiazlizePkmnList();


};

#endif // PKMN_SPECIES_DESCRIPTOR
