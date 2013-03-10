#include "pkmnparametercontroller.h"

#include "pkmncomputevaluesutility.h"
#include "pkmnspecies.h"
#include "pkmnaliment.h"
#include "pkmnmove.h"


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
      (parameter & (MAXHP | ATT | DEF | SPD | SPC | TYPE1 | TYPE2)))
    return;

  if (parameter & IV)
    manageParamIV(parameter, newValue);
  else if (parameter & (HP | MAXHP))
    manageParamHP(parameter, newValue);
  else if (parameter & (LEVEL | LEVELN | EXP))
    manageParamLvl(parameter, newValue);
  else if (parameter & (SPECIES))
    manageParamSpecies(parameter, newValue);
  else if (parameter & (ALIMENT))
    manageParamAliment(parameter, newValue);
  else if (parameter & (MOVE1PP | MOVE2PP | MOVE3PP | MOVE4PP))
    manageParamPP(parameter, newValue);
  else {
    // Performs standard value check!
    setCurrentPkmnParam(parameter, newValue);
  }

}

void PkmnParameterController::manageParamIV(
    int parameter,
    int newValue) {

  if (parameter & (MOVE1PP | MOVE2PP | MOVE3PP | MOVE4PP)) {

    if (newValue < 0 || newValue > 3) {
      emit operationOutcomeEvent(false,
                                 "Invalid value for PPUP.");
      return;
    }

    int oldValue = getCurrentPkmnParam(parameter^IV);
    int value = 0 | (newValue<<6) | (oldValue&0x3F);
    setCurrentPkmnParam(parameter^IV, value);

  } else if (parameter & (HP | ATT | DEF | SPD | SPC)) {

    if (newValue < 0 || newValue > 15) {
      emit operationOutcomeEvent(false,
                                 "Invalid value for IV.");
      return;
    }

    int oldValue = getCurrentPkmnParam(IV);
    int value;
    if (parameter & HP) {
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
    setCurrentPkmnParam(IV, value);

  }
}

void PkmnParameterController::manageParamHP(
    int parameter,
    int newValue) {

  if (newValue < 1) {
    emit operationOutcomeEvent(false,
                               "Invalid value for HP/MAXHP.");
    return;
  }

  int oldHP    = getCurrentPkmnParam(HP);
  int oldMaxHP = getCurrentPkmnParam(MAXHP);

  // Adjust HP/MAXHP with the new value bound:
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
  }
  setCurrentPkmnParam(LEVEL,  newValue);
  setCurrentPkmnParam(LEVELN, newValue);

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
  setCurrentPkmnParam(
       MAXHP,
       PkmnComputeValuesUtility::computeStat(
         descriptor, MAXHP, pkmnLevel, pkmn.get(HPEV), pkmn.get(IV)));
  setCurrentPkmnParam(
       ATT,
       PkmnComputeValuesUtility::computeStat(
         descriptor, ATT, pkmnLevel, pkmn.get(ATTEV), pkmn.get(IV)));
  setCurrentPkmnParam(
       DEF,
       PkmnComputeValuesUtility::computeStat(
         descriptor, DEF, pkmnLevel, pkmn.get(DEFEV), pkmn.get(IV)));
  setCurrentPkmnParam(
       SPD,
       PkmnComputeValuesUtility::computeStat(
         descriptor, SPD, pkmnLevel, pkmn.get(SPDEV), pkmn.get(IV)));
  setCurrentPkmnParam(
       SPC,
       PkmnComputeValuesUtility::computeStat(
         descriptor, SPC, pkmnLevel, pkmn.get(SPCEV), pkmn.get(IV)));

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
