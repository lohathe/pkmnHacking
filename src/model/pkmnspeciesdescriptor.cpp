#include "pkmnspeciesdescriptor.h"

#include <fstream>
#include <iostream>
#include <cstdio>

MoveLevel::MoveLevel(int level, int move) : _level(level), _move(move) {}
int MoveLevel::getLevel() const { return _level; }
int MoveLevel::getMove() const { return _move; }

PkmnSpeciesDescriptor::PkmnSpeciesDescriptor (
    int pkmnIndex,
    int pkmnEvolutionMethod,
    int levelingSpeed,
    int basicHp,
    int basicAtt,
    int basicDef,
    int basicSpd,
    int basicSpc,
    vector<MoveLevel> learningSet)
  : _pkmnIndex(pkmnIndex),
    _pkmnEvolutionMethod(pkmnEvolutionMethod),
    _levelingSpeed(levelingSpeed),
    _basicHp(basicHp),
    _basicAtt(basicAtt),
    _basicDef(basicDef),
    _basicSpd(basicSpd),
    _basicSpc(basicSpc),
    _learningSet(learningSet) { }

int PkmnSpeciesDescriptor::getIndex() const { return _pkmnIndex; }
int PkmnSpeciesDescriptor::getEvMethod() const { return _pkmnEvolutionMethod; }
int PkmnSpeciesDescriptor::getLvlSpeed() const { return _levelingSpeed; }
int PkmnSpeciesDescriptor::getBasicHP() const { return _basicHp; }
int PkmnSpeciesDescriptor::getBasicAtt() const { return _basicAtt; }
int PkmnSpeciesDescriptor::getBasicDef() const { return _basicDef; }
int PkmnSpeciesDescriptor::getBasicSpd() const { return _basicSpd; }
int PkmnSpeciesDescriptor::getBasicSpc() const { return _basicSpd; }
vector<MoveLevel> PkmnSpeciesDescriptor::getLearningSet() const {
  return _learningSet;
}
vector<int> PkmnSpeciesDescriptor::getNextEvolutions() const {
  vector<int> result;
  int index = _pkmnIndex;
  bool stop = false;
  while (index < 151 && !stop) {
    index = index + 1;
    if (PkmnSpeciesDescriptorList::get(index) -> getEvMethod() != 0)
      result.push_back(index);
    else
      stop = true;
  }
  return result;
}
vector<int> PkmnSpeciesDescriptor::getPrevEvolutions() const {
  vector<int> result;
  int index = _pkmnIndex;
  bool stop = false;

  if (_pkmnEvolutionMethod == 0)
    return result;

  while (index > 0 && !stop) {
    index = index - 1;
    if (PkmnSpeciesDescriptorList::get(index) -> getEvMethod() != 0)
      result.push_back(index);
    else {
      result.push_back(index);
      stop = true;
    }
  }
  return result;
}

PkmnSpeciesDescriptor *PkmnSpeciesDescriptorList::_pkmnList[] = {NULL};

PkmnSpeciesDescriptor *PkmnSpeciesDescriptorList::get(int index) {

  if (PkmnSpeciesDescriptorList::_pkmnList[0] == NULL)
    initiazlizePkmnList();

  if (index < 0 || index > 151)
    index = 0;

  return PkmnSpeciesDescriptorList::_pkmnList[index];

}

void PkmnSpeciesDescriptorList::initiazlizePkmnList() {

  std::ifstream infile(":/img/pkmndescriptor");

  for (int i=0; i<151; ++i) {

    char line[80];
    int index, evmethod, lvlspeed, hp, att, def, spd, spc, lvlmv, mv;
    vector<MoveLevel> learnset;

    infile.getline(line, 80);
    std::sscanf(line, "%d %d %d %d %d %d %d %d",
                &index, &evmethod, &lvlspeed, &hp, &att, &def, &spd, &spc);
    infile.getline(line, 80);
    while (std::sscanf(line, "%d %d", &lvlmv, &mv) == 2) {
      learnset.push_back(MoveLevel(lvlmv, mv));
    }

    PkmnSpeciesDescriptorList::_pkmnList[i] =
        new PkmnSpeciesDescriptor(
          index, evmethod, lvlspeed, hp, att, def, spd, spc, learnset);

  }

}
