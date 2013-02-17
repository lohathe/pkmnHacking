#include "pkmnsavestatemodel.h"


PkmnSaveStateModel::PkmnSaveStateModel (PkmnSaveState *savestate) :
  _saveState(savestate) {

}

int PkmnSaveStateModel::getTrainerId() const {

  return _saveState -> getTrainerId();

}

vector<const PkmnSpecies *> PkmnSaveStateModel::getPartyPkmnList() const {

  return _saveState -> getPartyPkmnList();

}

int PkmnSaveStateModel::getPartyPkmnCount() const {

  return _saveState -> getPartyPkmnCount();

}

int  PkmnSaveStateModel::getPartyPkmnParameter(int partyIndex, int info) {

  return _saveState -> getPartyPkmnParameter(partyIndex, info);

}

string PkmnSaveStateModel::getPartyPkmnName(int partyIndex) {

  return _saveState -> getPartyPkmnName(partyIndex);

}

PkmnState PkmnSaveStateModel::getPartyPkmnInfo(int partyIndex) const {

  return _saveState -> getPartyPkmnState(partyIndex);
}

bool PkmnSaveStateModel::setPartyPkmnParameter(int partyIndex, int info, int value) {

  bool outcome;
  outcome = _saveState -> setPartyPkmnParameter(partyIndex, info, value);

  if (outcome) {
    emit changedPkmnPartyInfoEvent();
    if (info == SPECIES)
      emit changedPkmnPartyListEvent();
  }

  return outcome;

}
bool PkmnSaveStateModel::setPartyPkmnStrParam(int partyIndex, int info, const string &value) {

  bool outcome;
  outcome = _saveState -> setPartyPkmnStrParam(partyIndex, info, value);

  if (outcome) {
    emit changedPkmnPartyInfoEvent();
  }

  return outcome;

}

bool PkmnSaveStateModel::createPartyPkmnAtIndex(int partyIndex, int species) {

  bool outcome;
  outcome = _saveState -> createPartyPkmnAtIndex(partyIndex, species);

  if (outcome) {
    emit changedPkmnPartyListEvent();
    emit changedPkmnPartyInfoEvent();
  }

  return outcome;

}

bool PkmnSaveStateModel::deletePartyPkmnAtIndex(int partyIndex) {

  bool outcome;
  outcome = _saveState -> deletePartyPkmnAtIndex(partyIndex);

  if (outcome) {
    emit changedPkmnPartyListEvent();
    emit changedPkmnPartyInfoEvent();
  }

  return outcome;

}

bool PkmnSaveStateModel::saveToFile() const {

  return _saveState -> saveToFile();

}

bool PkmnSaveStateModel::openFile(const string &filepath) {

  bool outcome;
  outcome = _saveState -> openFile(filepath);

  if (outcome) {
    emit changedPkmnPartyInfoEvent();
    emit changedPkmnPartyListEvent();
    emit changedPkmnPokedexEvent();
  }

  return outcome;

}

PkmnPokedex PkmnSaveStateModel::getPkmnPokedex() const {

  return _saveState -> getPkmnPokedex();

}

bool PkmnSaveStateModel::setPkmnPokedexSeen(int pkmnIndex, bool isSeen) {

  bool outcome = _saveState -> setPkmnPokedexSeen(pkmnIndex, isSeen);
  if (outcome)
    emit changedPkmnPokedexEvent();
  return outcome;

}

bool PkmnSaveStateModel::setPkmnPokedexCatched(int pkmnIndex, bool isCatched) {

  bool outcome = _saveState -> setPkmnPokedexCatched(pkmnIndex, isCatched);
  if (outcome)
    emit changedPkmnPokedexEvent();
  return outcome;

}
