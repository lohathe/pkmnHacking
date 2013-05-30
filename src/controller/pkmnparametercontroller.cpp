#include "pkmnparametercontroller.h"

#include "pkmncomputevaluesutility.h"
#include "pkmnspecies.h"
#include "pkmnaliment.h"
#include "pkmnmove.h"

#include "sstream"

PkmnParameterController::PkmnParameterController(
    bool coherencyEnabled) :
  _coherencyEnabled(coherencyEnabled) {}

void PkmnParameterController::manageEnableCoherency(bool enabled) {

  _coherencyEnabled = enabled;

}

void PkmnParameterController::managePkmnStrParamChanged(
    int info,
    const string &newValue) {

  if (!isCurrentPkmnValid()) {
    return;
  }

  if (newValue.size() > 10) {
    emit operationOutcomeEvent(false,
                               "Pokemon nickname cannot have more than 10 characters.");
    return;
  }

  setCurrentPkmnStrParam(info, newValue);

}

void PkmnParameterController::managePkmnParamChanged(
    int parameter,
    int newValue) {

  if (!isCurrentPkmnValid()) {
    return;
  }

  if (_coherencyEnabled &&
      !(parameter & IV) &&
      (parameter & (MAXHP | ATT | DEF | SPD | SPC | TYPE1 | TYPE2)))
    return;

  if (parameter & IV)
    manageParamIV(parameter, newValue);
  else if (parameter & (HP | MAXHP))
    manageParamHP(parameter, newValue);
  else if (parameter & (LEVEL | LEVELN))
    manageParamLvl(parameter, newValue);
  else if (parameter & (SPECIES))
    manageParamSpecies(parameter, newValue);
  else if (parameter & (ALIMENT))
    manageParamAliment(parameter, newValue);
  else if (parameter & (MOVE1PP | MOVE2PP | MOVE3PP | MOVE4PP))
    manageParamPP(parameter, newValue);
  else if (parameter & EXP)
    manageParamExp(parameter, newValue);
  else if (parameter & (HPEV | ATTEV | DEFEV | SPDEV | SPCEV))
    manageParamEV(parameter, newValue);
  else {
    // Performs standard value check!
    setCurrentPkmnParam(parameter, newValue);
  }

}

void PkmnParameterController::manageParamIV(
    int parameter,
    int newValue) {

  if (parameter & (MOVE1PP | MOVE2PP | MOVE3PP | MOVE4PP)) {

    // Check if the new value is in the right range.
    // Otherwise round the value to the nearest valid value.
    if (newValue < 0 || newValue >3) {
      newValue = roundToNearestValue(newValue, 0, 3);
      std::ostringstream message;
      message << "Invalid value for PPUP: using limit value " << newValue;
      emit operationOutcomeEvent(false, message.str());
    }

    // Getting older values
    int oldValue = getCurrentPkmnParam(parameter^IV);
    int oldPPUP  = (oldValue >> 6) & 0x03;

    // Check if some changes are happening. If no changes abort procedure.
    if (oldPPUP == newValue)
      return;

    // Get info about the move which PPUP is being modified.
    const PkmnMove *move = PkmnMoveList::get(getCurrentPkmnParam((parameter^IV)>>12));
    int newPP = move -> getMaxPP(newValue);

    // Compute the new value combining the new PPUP and the corresponding
    // max PP for the specific move with the new PPUP
    int value = 0 | (newValue << 6) | (newPP & 0x3F);

    setCurrentPkmnParam(parameter^IV, value);

  } else if (parameter & (MAXHP | ATT | DEF | SPD | SPC)) {

    // Check if the new value is in the right range.
    // Otherwise round the value to the nearest valid value.
    if (newValue < 0 || newValue > 15) {

      newValue = roundToNearestValue(newValue, 0, 15);
      std::ostringstream message;
      message << "Invalid value for IV: using limit value " << newValue;
      emit operationOutcomeEvent(false, message.str());
    }

    // Getting old values
    int oldValue = getCurrentPkmnParam(IV);

    int value;
    if (parameter & MAXHP) {
      value = oldValue & 0xEEEE;
      value = value | ((newValue<<0) & 0x0001) | ((newValue<<3) & 0x0010) |
                      ((newValue<<6) & 0x0100) | ((newValue<<9) & 0x1000);
    } else if (parameter & ATT) {
      value = (oldValue & 0x0FFF) | ((newValue<<12) & 0xF000);
    } else if (parameter & DEF) {
      value = (oldValue & 0xF0FF) | ((newValue<<8) & 0x0F00);
    } else if (parameter & SPD) {
      value = (oldValue & 0xFF0F) | ((newValue<<4) & 0x00F0);
    } else { // (parameter & SPC)
      value = (oldValue & 0xFFF0) | ((newValue<<0) & 0x000F);
    }

    // Check if the new value has changed. If not abort procedure.
    if (value == oldValue)
      return;

    // Update STATS value considering the new value for IV.
    if (_coherencyEnabled) {

      // Get the corresponding stat ev
      int statev = getCurrentPkmnParam((parameter^IV) >> 11);
      // Compute new stat value
      int stat = PkmnComputeValuesUtility::computeStat(
            getCurrentPkmnSpeciesDescriptor(),
            parameter ^ IV,
            getCurrentPkmnInfo().get(LEVEL),
            statev,
            value);
      // Update stat value if changed
      if (getCurrentPkmnInfo().get(parameter ^ IV) != stat)
        setCurrentPkmnParam(parameter^IV, stat);

    }

    setCurrentPkmnParam(IV, value);

  }
}

void PkmnParameterController::manageParamHP(
    int parameter,
    int newValue) {

  // Check if the new value is in the right range.
  // Otherwise round the value to the nearest valid value.
  if (newValue < 1 /*|| newValue > 999*/) {
    newValue = roundToNearestValue(newValue, 1, 10000);
    std::ostringstream message;
    message << "Invalid value for HP/MAXHP: using limit value " << newValue;
    emit operationOutcomeEvent(false, message.str());
  }

  int oldHP    = getCurrentPkmnParam(HP);
  int oldMaxHP = getCurrentPkmnParam(MAXHP);

  // Check if the value changed from the old one. If not abort procedure.
  if ((parameter == HP && oldHP == newValue) ||
      (parameter == MAXHP && oldMaxHP == newValue))
    return;

  // Compute new HP/MAXHP with the new value bound:
  // if newValue is greater than MAXHP => update MAXHP
  // if newValue is smaller than HP    => update HP
  if ((parameter == HP) && (newValue > oldMaxHP)) {
    if (_coherencyEnabled) {
      emit operationOutcomeEvent(false,
                                 "Cannot have more HP than MAXHP.");
      return;
    }
    setCurrentPkmnParam(MAXHP, newValue);
  } else if ((parameter == MAXHP) && (newValue < oldHP)) {
    setCurrentPkmnParam(HP, newValue);
  }
  setCurrentPkmnParam(parameter, newValue);

}

void PkmnParameterController::manageParamLvl(
    int,
    int newValue) {

  if (newValue < 1 || newValue > 100) {
    newValue = roundToNearestValue(newValue, 1, 100);
    std::ostringstream message;
    message << "Invalid value for Level: using limit value " << newValue;
    emit operationOutcomeEvent(false, message.str());
  }

  // If no changes happend, abort procedure.
  if (getCurrentPkmnParam(LEVEL) == newValue)
    return;

  // Synchronize level and experience
  if (_coherencyEnabled) {
    const PkmnSpeciesDescriptor *descriptor = getCurrentPkmnSpeciesDescriptor();
    int expPrev = PkmnComputeValuesUtility::computeExpForLevel(descriptor, newValue);
    int expNext = PkmnComputeValuesUtility::computeExpForLevel(descriptor, newValue+1);
    int exp = getCurrentPkmnParam(EXP);
    // If levelUp => update to bigger exp
    // If levelDown => update with smaller exp
    if (exp < expPrev || exp >= expNext)
      setCurrentPkmnParam(EXP, expPrev);
    updateStatsValue(descriptor, getCurrentPkmnInfo(), newValue);
  }
  setCurrentPkmnParam(LEVEL,  newValue);
  setCurrentPkmnParam(LEVELN, newValue);

}

void PkmnParameterController::manageParamExp(
    int,
    int newValue) {

  const PkmnSpeciesDescriptor *descriptor = getCurrentPkmnSpeciesDescriptor();
  int maxExp = PkmnComputeValuesUtility::computeExpForLevel(descriptor, 100);

  if (newValue < 1 ||
      newValue > maxExp) {
    newValue = roundToNearestValue(newValue, 1, maxExp);
    emit operationOutcomeEvent(false,
                               "Invalid value for exp: using limit value.");
  }

  // If no changes happend, abort procedure
  if (getCurrentPkmnParam(EXP) == newValue)
    return;

  // If in coherency mode need to update the level, an if the level changed
  // due to exp variation, need to recompute stat values.
  if (_coherencyEnabled) {
    int oldLevel = getCurrentPkmnParam(LEVEL);
    int newLevel = PkmnComputeValuesUtility::computeLevelForExp(descriptor, newValue);
    if (oldLevel != newLevel) {

      setCurrentPkmnParam(LEVEL, newLevel);
      setCurrentPkmnParam(LEVELN, newLevel);
      updateStatsValue(descriptor, getCurrentPkmnInfo(), newValue);

    }
  }

  setCurrentPkmnParam(EXP, newValue);

}

void PkmnParameterController::manageParamEV(
    int parameter,
    int newValue) {

  // All EV values have the same range
  int maxValueEV = PkmnState::getMaxValue(ATTEV);
  if (newValue < 0 || newValue > maxValueEV) {
    newValue = roundToNearestValue(newValue, 0, maxValueEV);
    emit operationOutcomeEvent(false,
                               "Invalid value for EV: using limit value.");
  }

  // If no changes happened, abort procedure.
  if (newValue == getCurrentPkmnParam(parameter))
    return;

  if (_coherencyEnabled) {
    updateStatsValue(getCurrentPkmnSpeciesDescriptor(),
                     getCurrentPkmnInfo(),
                     getCurrentPkmnInfo().get(LEVEL));
  }

  setCurrentPkmnParam(parameter, newValue);

}

void PkmnParameterController::manageParamSpecies(
    int,
    int newValue) {

  const PkmnSpecies *pkmn = PkmnSpeciesList::getById(newValue);
  if (!(pkmn -> isValid())) {
    emit operationOutcomeEvent(false,
                               "Invalid pokemon species.");
    return;
  }

  setCurrentPkmnStrParam(PKMNNAME, pkmn->getUpperCaseName());
  setCurrentPkmnParam(SPECIES, pkmn->getId());
  setCurrentPkmnParam(TYPE1, pkmn->getElement1());
  setCurrentPkmnParam(TYPE2, pkmn->getElement2());

}

void PkmnParameterController::manageParamAliment(
    int,
    int newValue) {

  if (!(newValue & (Aliment::ASLEEP | Aliment::BURNED | Aliment::FROZEN |
                  Aliment::PARALYZED | Aliment::POISONED))) {
    emit operationOutcomeEvent(false,
                               "Invalid pokemon aliment.");
    return;
  }

  // Compute new status as old status where the clicked aliment
  // is switched on/off
  int oldValue = getCurrentPkmnParam(ALIMENT);
  int value = oldValue^newValue;

  setCurrentPkmnParam(ALIMENT, value);

}

void PkmnParameterController::manageParamPP(
    int parameter,
    int newValue) {

  if (newValue < 0 || newValue > 63) {
    emit operationOutcomeEvent(false,
                               "Invalid move PP value.");
    return;
  }

  // Need to compose PP value: combine PPUP and effective PP.
  int oldValue = getCurrentPkmnParam(parameter);
  int value = (oldValue & 0xC0) | (newValue & 0x3F);

  setCurrentPkmnParam(parameter, value);

}

void PkmnParameterController::setPkmnBasicStats() {

  const PkmnState pkmn = getCurrentPkmnInfo();
  const PkmnSpecies *species = PkmnSpeciesList::getById(pkmn.get(SPECIES));
  const PkmnSpeciesDescriptor *descriptor =
      PkmnSpeciesDescriptorList::get(species->getIndex());
  const vector<MoveLevel>  learnset = descriptor->getLearningSet();
  int pkmnLevel = pkmn.get(LEVEL);

  // setting right amount of exp referring to level
  setCurrentPkmnParam(
       EXP,
       PkmnComputeValuesUtility::computeExpForLevel(descriptor, pkmnLevel));

  // setting stats values
  updateStatsValue(descriptor, pkmn, pkmnLevel);

  // setting default moves
  unsigned int i = 0;
  for (;
       i<learnset.size() && learnset[i].getLevel() <= pkmnLevel;
       ++i) {
    int infoMove, infoPP;
    if (i%4 == 0) { infoMove = MOVE1; infoPP = MOVE1PP; }
    else if (i%4 == 1) { infoMove = MOVE2; infoPP = MOVE2PP; }
    else if (i%4 == 2) { infoMove = MOVE3; infoPP = MOVE3PP; }
    else { infoMove = MOVE4; infoPP = MOVE4PP; }
    setCurrentPkmnParam(
         infoMove,
         learnset[i].getMove());
    setCurrentPkmnParam(
          infoPP,
          PkmnMoveList::get(learnset[i].getMove())->getPP());
  }
  // deleting old move if any
  for (; i<4; ++i) {
    int infoMove, infoPP;
    if (i%4 == 0) { infoMove = MOVE1; infoPP = MOVE1PP; }
    else if (i%4 == 1) { infoMove = MOVE2; infoPP = MOVE2PP; }
    else if (i%4 == 2) { infoMove = MOVE3; infoPP = MOVE3PP; }
    else { infoMove = MOVE4; infoPP = MOVE4PP; }
    setCurrentPkmnParam( infoMove, 0);
    setCurrentPkmnParam( infoPP, 0);
  }

}

void PkmnParameterController::updateStatsValue(
    const PkmnSpeciesDescriptor *descriptor,
    const PkmnState pkmn,
    int pkmnLevel) {

  int newValue;

  newValue = PkmnComputeValuesUtility::computeStat(
        descriptor, MAXHP, pkmnLevel, pkmn.get(HPEV), pkmn.get(IV));
  if (newValue != getCurrentPkmnParam(MAXHP)) {
    setCurrentPkmnParam(MAXHP, newValue);
    // Update current HP if higher than MAXHP
    if (getCurrentPkmnParam(HP) > getCurrentPkmnParam(MAXHP))
      setCurrentPkmnParam(HP, getCurrentPkmnParam(MAXHP));
  }

  newValue = PkmnComputeValuesUtility::computeStat(
        descriptor, ATT, pkmnLevel, pkmn.get(ATTEV), pkmn.get(IV));
  if (newValue != getCurrentPkmnParam(ATT))
    setCurrentPkmnParam(ATT, newValue);

  newValue = PkmnComputeValuesUtility::computeStat(
        descriptor, DEF, pkmnLevel, pkmn.get(DEFEV), pkmn.get(IV));
  if (newValue != getCurrentPkmnParam(DEF))
    setCurrentPkmnParam(DEF, newValue);

  newValue = PkmnComputeValuesUtility::computeStat(
        descriptor, SPD, pkmnLevel, pkmn.get(SPDEV), pkmn.get(IV));
  if (newValue != getCurrentPkmnParam(SPD))
    setCurrentPkmnParam(SPD, newValue);

  newValue = PkmnComputeValuesUtility::computeStat(
        descriptor, SPC, pkmnLevel, pkmn.get(SPCEV), pkmn.get(IV));
  if (newValue != getCurrentPkmnParam(SPC))
    setCurrentPkmnParam(SPC, newValue);

}

int PkmnParameterController::roundToNearestValue(
    int originalValue,
    int minValue,
    int maxValue) const {

  if (originalValue < minValue) return minValue;
  if (originalValue > maxValue) return maxValue;
  return originalValue;

}
