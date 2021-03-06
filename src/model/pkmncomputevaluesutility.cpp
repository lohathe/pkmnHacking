#include "pkmncomputevaluesutility.h"
#include "pkmnstate.h"

#include <math.h>

int PkmnComputeValuesUtility::computeExpForLevel(
    const PkmnSpeciesDescriptor *descriptor,
    int level) {

  if (level < 1)
    return 1;

  int result = 1;

  if (descriptor->getLvlSpeed() == PkmnSpeciesDescriptor::FAST) {
    result = (4*level*level*level)/5;
  } else if (descriptor->getLvlSpeed() == PkmnSpeciesDescriptor::MEDIUMFAST) {
    result = level*level*level;
  } else if (descriptor->getLvlSpeed() == PkmnSpeciesDescriptor::MEDIUMSLOW) {
    result = (6*level*level*level)/5 - 15*level*level + 100*level -140;
  } else if (descriptor->getLvlSpeed() == PkmnSpeciesDescriptor::SLOW) {
    result = (5*level*level*level)/4;
  }

  if (result < 1) result = 1;

  return result;

}

int PkmnComputeValuesUtility::computeLevelForExp(
    const PkmnSpeciesDescriptor *descriptor,
    int exp) {
/*
  bool stop = false;
  int levelmin = 1;
  int levelmax = 100;
  int level = 50;

  while (!stop) {

    int temp = PkmnComputeValuesUtility::computeExpForLevel(descriptor, level);
    if (temp >= exp)
      levelmax = level;
    else
      levelmin = level;

    level = (levelmin + levelmax)/2;

    if (levelmax - levelmin <= 1) {
      stop = true;
    }
  return levelmin;

  }*/

  int level = 1;
  int inf = PkmnComputeValuesUtility::computeExpForLevel(descriptor, 1);
  int sup = PkmnComputeValuesUtility::computeExpForLevel(descriptor, 2);
  bool stop = false;
  while (!stop) {
    if (inf <= exp && exp < sup)
      stop = true;
    else {
      level ++;
      inf = sup;
      sup = PkmnComputeValuesUtility::computeExpForLevel(descriptor, level+1);
    }
  }

  return level;

}

int PkmnComputeValuesUtility::computeStat(
    const PkmnSpeciesDescriptor *descriptor,
    int stat,
    int level,
    int ev,
    int iv) {

  int result = 1;

  if (stat == MAXHP) {
    int usediv = 0 | ((iv>>12)&0x08) | ((iv>>9)&0x04) | ((iv>>6)&0x02) | ((iv>>3)&0x01);
    result = ((usediv + descriptor->getBasicHP() + sqrt(ev)/8 + 50)*level)/50 + 10;
  } else {
    int base = 1;
    int usediv = 0;
    if (stat == ATT) {
      base = descriptor->getBasicAtt();
      usediv = (iv>>12)&0x0F;
    } else if (stat == DEF) {
      base = descriptor->getBasicDef();
      usediv = (iv>>8)&0x0F;
    } else if (stat == SPD) {
      base = descriptor->getBasicSpd();
      usediv = (iv>>4)&0x0F;
    } else if (stat == SPC) {
      base = descriptor->getBasicSpc();
      usediv = (iv>>0)&0x0F;
    }
    result = ((usediv + base + sqrt(ev)/8)*level)/50 + 5;
  }

  return result;

}
