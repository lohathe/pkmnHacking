#ifndef PKMN_COMPUTE_VALUES_UTILITY
#define PKMN_COMPUTE_VALUES_UTILITY

#include "pkmnspeciesdescriptor.h"

class PkmnComputeValuesUtility {

public:

  static int computeExpForLevel(const PkmnSpeciesDescriptor *, int);
  static int computeLevelForExp(const PkmnSpeciesDescriptor *, int);
  static int computeStat(const PkmnSpeciesDescriptor *, int, int, int, int);

};

#endif // PKMN_COMPUTE_VALUES_UTILITY
