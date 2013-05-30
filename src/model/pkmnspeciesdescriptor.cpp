#include "pkmnspeciesdescriptor.h"

#include "pkmnspecies.h"
#include "pkmnmove.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdio>

#include <QFile>

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
//{
//  for (unsigned int i=0; i<learningSet.size(); ++i)
//    _learningSet.push_back(MoveLevel(learningSet[i].getLevel(), learningSet[i].getMove()));
//}

int PkmnSpeciesDescriptor::getIndex() const { return _pkmnIndex; }
int PkmnSpeciesDescriptor::getEvMethod() const { return _pkmnEvolutionMethod; }
string PkmnSpeciesDescriptor::getEvMethodString() const {
  string result;
  if (_pkmnEvolutionMethod == 0) result = "base";
  else if (_pkmnEvolutionMethod >= 1) result = "lvl "+ static_cast<std::ostringstream*>( &(std::ostringstream() << _pkmnEvolutionMethod) )->str();
  else if (_pkmnEvolutionMethod == PkmnSpeciesDescriptor::TRADE) result = "trade";
  else if (_pkmnEvolutionMethod == PkmnSpeciesDescriptor::FIRESTONE) result = "fstone";
  else if (_pkmnEvolutionMethod == PkmnSpeciesDescriptor::WATERSTONE) result = "wstone";
  else if (_pkmnEvolutionMethod == PkmnSpeciesDescriptor::THUNDERSTONE) result = "tstone";
  else if (_pkmnEvolutionMethod == PkmnSpeciesDescriptor::LEAFSTONE) result = "lstone";
  else if (_pkmnEvolutionMethod == PkmnSpeciesDescriptor::MOONSTONE) result = "mstone";
  return result;
}
int PkmnSpeciesDescriptor::getLvlSpeed() const { return _levelingSpeed; }
int PkmnSpeciesDescriptor::getBasicHP() const { return _basicHp; }
int PkmnSpeciesDescriptor::getBasicAtt() const { return _basicAtt; }
int PkmnSpeciesDescriptor::getBasicDef() const { return _basicDef; }
int PkmnSpeciesDescriptor::getBasicSpd() const { return _basicSpd; }
int PkmnSpeciesDescriptor::getBasicSpc() const { return _basicSpc; }
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

const PkmnSpeciesDescriptor *PkmnSpeciesDescriptorList::get(int index) {

  if (PkmnSpeciesDescriptorList::_pkmnList[0] == NULL)
    initiazlizePkmnList();

  if (index < 0 || index > 151)
    index = 0;

  return PkmnSpeciesDescriptorList::_pkmnList[index];

}

void PkmnSpeciesDescriptorList::initiazlizePkmnList() {

  std::ifstream infile;
  infile.open("./pkmndescriptor", std::ios::in);

  for (int i=0; i<152; ++i) {

    char line[80];
    int index, evmethod, lvlspeed, hp, att, def, spd, spc, lvlmv, mv;
    vector<MoveLevel> learnset;

    infile.getline(line, 80);
    std::sscanf(line, "%d %d %d %d %d %d %d %d",
                &index, &evmethod, &lvlspeed, &hp, &att, &def, &spd, &spc);
    infile.getline(line, 80);
    while (std::sscanf(line, "%d %d", &lvlmv, &mv) == 2) {
      learnset.push_back(MoveLevel(lvlmv, mv));
      infile.getline(line, 80);
    }

    PkmnSpeciesDescriptorList::_pkmnList[i] =
        new PkmnSpeciesDescriptor(
          index, evmethod, lvlspeed, hp, att, def, spd, spc, learnset);

  }
/*
  for (int i=0; i<152; ++i) {

    if (PkmnSpeciesDescriptorList::get(i)->getLvlSpeed() == 4)
      std::cout<<PkmnSpeciesList::getByIndex(PkmnSpeciesDescriptorList::get(i)->getIndex())->getName()<<std::endl;

  }*/

}

void PkmnSpeciesDescriptorList::print(int start, int stop) {

  for (int i=start; i<stop; i++) {
    const PkmnSpeciesDescriptor *desc = PkmnSpeciesDescriptorList::get(i);
    printf("%s : %d %d %d %d %d\n",
           PkmnSpeciesList::getByIndex(desc->getIndex())->getName().c_str(),
           desc->getBasicHP(),
           desc->getBasicAtt(),
           desc->getBasicDef(),
           desc->getBasicSpd(),
           desc->getBasicSpc());
    vector<MoveLevel> moves = desc->getLearningSet();
    for (unsigned int j=0; j<moves.size(); ++j) {
      printf("  %d\t:%s\n",
             moves[j].getLevel(), PkmnMoveList::get(moves[j].getMove())->getName().c_str());
    }
    printf("----------------%d\n\n", i);
  }

}

