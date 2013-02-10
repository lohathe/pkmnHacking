#include "pkmnspeciesdescriptor.h"

PkmnSpeciesDescriptor::PkmnSpeciesDescriptor (
    int pkmnIndex,
    int pkmnEvolveFrom,
    int pkmnEvolutionMethod,
    int levelingSpeed,
    int basicHp,
    int basicAtt,
    int basicDef,
    int basicSpd,
    int basicSpc,
    vector<MoveLevel> learningSet)
  : _pkmnIndex(pkmnIndex),
    _pkmnEvolveFrom(pkmnEvolveFrom),
    _pkmnEvolutionMethod(pkmnEvolutionMethod),
    _levelingSpeed(levelingSpeed),
    _basicHp(basicHp),
    _basicAtt(basicAtt),
    _basicDef(basicDef),
    _basicSpd(basicSpd),
    _basicSpc(basicSpc),
    _learningSet(learningSet) { }

