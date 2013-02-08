#include "pkmnpartycontroller.h"
#include "pkmnpartyview.h"
#include "pkmnsavestatemodel.h"
#include "pkmnaliment.h"

#include <QObject>

PkmnPartyController::PkmnPartyController (PkmnSaveStateModel *model,
                                          PkmnPartyView *view) :
  _selectedPartyIndex(0), _isCreatingPkmn(false), _isChangingMove(false),
  _selectedMoveIndex(0), _model(model), _view(view) {

  connect(_view, SIGNAL(partyPkmnSelectedEvent(int)),
          this,  SLOT(managePartyPkmnSelected(int)));

  connect(_view, SIGNAL(createPkmnEvent()), this, SLOT(manageCreatePkmn()));
  connect(_view, SIGNAL(deletePkmnEvent()), this, SLOT(manageDeletePkmn()));

  connect(_view, SIGNAL(pkmnSpeciesChangeEvent()),
          this,  SLOT(manageSpeciesChange()));
  connect(_view, SIGNAL(pkmnSpeciesSelectedEvent(int)),
          this,  SLOT(managePkmnSpeciesSelected(int)));
  connect(_view, SIGNAL(pkmnNameChangedEvent(string)),
          this,  SLOT(managePkmnNameChanged(string)));
  connect(_view, SIGNAL(pkmnParameterChangedEvent(int,int)),
          this,  SLOT(managePkmnParameterChanged(int,int)));
  connect(_view, SIGNAL(pkmnMoveChangeEvent(int)),
          this,  SLOT(manageMoveChange(int)));
  connect(_view, SIGNAL(pkmnMoveSelectedEvent(int)),
          this,  SLOT(managePkmnMoveSelected(int)));

  // ACTIVATE VIEW
  _view -> connectModel(model);
  _view -> manageChangedPkmnPartyList();

}

void PkmnPartyController::managePartyPkmnSelected(int selectedPartyIndex) {

  if (selectedPartyIndex < 1 || selectedPartyIndex > 6) {
    emit operationOutcomeEvent(false,
                               "No valid party pokemon selected.");
    return;
  }

  _isCreatingPkmn = false;
  _isChangingMove = false;
  _selectedPartyIndex = selectedPartyIndex;

  _view -> setSelectedPartyPkmn(_selectedPartyIndex);
  _view -> displayPkmnInfo();

}

void PkmnPartyController::manageCreatePkmn() {

  if (_model -> getPartyPkmnCount() >= 6) {
    emit operationOutcomeEvent(false,
                               "Cannot have more than 6 pokemon in party.");
    return;
  }

  _isCreatingPkmn = true;
  _isChangingMove = false;

  _view -> displaySpeciesPicker();

}

void PkmnPartyController::manageDeletePkmn() {

  bool outcome = true;

  _isCreatingPkmn = false;
  _isChangingMove = false;

  if (_selectedPartyIndex < 1 || _selectedPartyIndex > 6) {
    emit operationOutcomeEvent(false,
                               "No valid pokemon in party selected.");
    return;
  }
  if (_model -> getPartyPkmnCount() <= 1) {
    emit operationOutcomeEvent(false,
                               "Cannot delete last pokemon in party.");
  }

  outcome = _model -> deletePartyPkmnAtIndex(_selectedPartyIndex);
  if (!outcome) {
    emit operationOutcomeEvent(false,
                               "Some error while deleting selected pokemon.");
    return;
  }

  _selectedPartyIndex = 0;

  _view -> setSelectedPartyPkmn(_selectedPartyIndex);
  _view -> displayPkmnInfo();

  emit operationOutcomeEvent(true,
                             "Successfully deleted selected pokemon from party.");

}

void PkmnPartyController::manageMoveChange(int selectedMoveIndex) {

  _isCreatingPkmn = false;
  _isChangingMove = true;
  _selectedMoveIndex = selectedMoveIndex;

  if (_selectedMoveIndex & (MOVE1 || MOVE2 || MOVE3 || MOVE4)) {
    emit operationOutcomeEvent(false,
                               "No valid move selected to be changed.");
    return;
  }

  _view -> displayMovePicker();

}

void PkmnPartyController::manageSpeciesChange() {

  _isCreatingPkmn = false;
  _isChangingMove = false;
  _view -> displaySpeciesPicker();

}

void PkmnPartyController::managePkmnSpeciesSelected(int selectedSpecies) {

  bool outcome = true;

  if (!(PkmnSpeciesList::get(selectedSpecies) -> isValid())) {
    emit operationOutcomeEvent(false,
                               "No valid pokemon species selected.");
    return;
  }

  if (_isCreatingPkmn) {
    _isCreatingPkmn = false;
    int partyIndex = _model -> getPartyPkmnCount() + 1;

    outcome = _model -> createPartyPkmnAtIndex(partyIndex, selectedSpecies);
    if (!outcome) {
      emit operationOutcomeEvent(false,
                                 "Some error while creating specified pokemon.");
      return;
    } else {
      _selectedPartyIndex = _model -> getPartyPkmnCount();
      emit operationOutcomeEvent(true,
                                 "Successfully created specified pokemon in party");
    }
  } else {
    managePkmnParameterChanged(SPECIES, selectedSpecies);
  }

  _isChangingMove = false;
  _view -> setSelectedPartyPkmn(_selectedPartyIndex);
  _view -> displayPkmnInfo();

}

void PkmnPartyController::managePkmnMoveSelected(int selectedMove) {

  if (!_isChangingMove ||
      !(_selectedMoveIndex & (MOVE1 | MOVE2 | MOVE3 | MOVE4))) {
    emit operationOutcomeEvent(false,
                               "No valid move selected.");
    return;
  }

  _isChangingMove = false;
  _isCreatingPkmn = false;
  _model -> setPartyPkmnParameter(_selectedPartyIndex, _selectedMoveIndex, selectedMove);

  _view -> displayPkmnInfo();

}

void PkmnPartyController::managePkmnNameChanged(const string &newName) {

  if (newName.size() > 10) {
    emit operationOutcomeEvent(false,
                               "Pokemon nickname cannot have more than 10 characters.");
    return;
  }
  _model -> setPartyPkmnName(_selectedPartyIndex, newName);

}

void PkmnPartyController::managePkmnParameterChanged(int parameter, int newValue) {

  if (parameter & IV)
    manageIVParameter(parameter, newValue);
  else if (parameter & (HP | MAXHP))
    manageHPParameter(parameter, newValue);
  else if (parameter & (LEVEL | LEVELN | EXP))
    manageLvlParameter(parameter, newValue);
  else if (parameter & (SPECIES))
    manageSpeciesParameter(parameter, newValue);
  else if (parameter & (ALIMENT))
    manageAlimentParameter(parameter, newValue);
  else if (parameter & (MOVE1PP | MOVE2PP | MOVE3PP | MOVE4PP))
    managePPParameter(parameter, newValue);
  else {
    // Performs standard value check!
    _model -> setPartyPkmnParameter(_selectedPartyIndex, parameter, newValue);
  }

}

void PkmnPartyController::manageIVParameter(int parameter, int newValue) {
  if (parameter & (MOVE1PP | MOVE2PP | MOVE3PP | MOVE4PP)) {

    if (newValue < 0 || newValue > 3) {
      emit operationOutcomeEvent(false,
                                 "Invalid value for PPUP.");
      return;
    }

    int oldValue = _model -> getPartyPkmnParameter(_selectedPartyIndex, parameter^IV);
    int value = 0 | (newValue<<6) | (oldValue&0x3F);
    _model -> setPartyPkmnParameter(_selectedPartyIndex, parameter^IV, value);

  } else if (parameter & (HP | ATT | DEF | SPD | SPC)) {

    if (newValue < 0 || newValue > 15) {
      emit operationOutcomeEvent(false,
                                 "Invalid value for IV.");
      return;
    }

    int oldValue = _model -> getPartyPkmnParameter(_selectedPartyIndex, IV);
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
    _model -> setPartyPkmnParameter(_selectedPartyIndex, IV, value);

  }
}

void PkmnPartyController::manageHPParameter(int parameter, int newValue) {

  if (newValue < 1) {
    emit operationOutcomeEvent(false,
                               "Invalid value for HP/MAXHP.");
    return;
  }

  int oldHP = _model -> getPartyPkmnParameter(_selectedPartyIndex, HP);
  int oldMaxHP = _model -> getPartyPkmnParameter(_selectedPartyIndex, MAXHP);


  if ((parameter == HP) && (newValue > oldMaxHP)) {
    _model -> setPartyPkmnParameter(_selectedPartyIndex, MAXHP, newValue);
  } else if ((parameter == MAXHP) && (newValue < oldHP)) {
    _model -> setPartyPkmnParameter(_selectedPartyIndex, HP, newValue);
  }
  _model -> setPartyPkmnParameter(_selectedPartyIndex, parameter, newValue);

}

void PkmnPartyController::manageLvlParameter(int parameter, int newValue) {

  // Synchronize level and experience
  _model -> setPartyPkmnParameter(_selectedPartyIndex, parameter, newValue);

}

void PkmnPartyController::manageSpeciesParameter(int, int newValue) {

  const PkmnSpecies *pkmn = PkmnSpeciesList::get(newValue);
  if (!(pkmn -> isValid())) {
    emit operationOutcomeEvent(false,
                               "Invalid pokemon species.");
    return;
  }

  _model -> setPartyPkmnName(_selectedPartyIndex, pkmn->getName());
  _model -> setPartyPkmnParameter(_selectedPartyIndex, SPECIES, pkmn->getId());
  _model -> setPartyPkmnParameter(_selectedPartyIndex, TYPE1, pkmn->getElement1());
  _model -> setPartyPkmnParameter(_selectedPartyIndex, TYPE2, pkmn->getElement2());

}

void PkmnPartyController::manageAlimentParameter(int, int newValue) {

  if (!(newValue & (Aliment::ASLEEP | Aliment::BURNED | Aliment::FROZEN |
                  Aliment::PARALYZED | Aliment::POISONED))) {
    emit operationOutcomeEvent(false,
                               "Invalid pokemon aliment.");
    return;
  }

  int oldValue = _model -> getPartyPkmnParameter(_selectedPartyIndex, ALIMENT);
  _model -> setPartyPkmnParameter(_selectedPartyIndex, ALIMENT, oldValue^newValue);

}

void PkmnPartyController::managePPParameter(int parameter, int newValue) {

  if (newValue < 0 || newValue > 63) {
    emit operationOutcomeEvent(false,
                               "Invalid move PP value.");
    return;
  }

  int oldValue = _model -> getPartyPkmnParameter(_selectedPartyIndex, parameter);
  int value = (oldValue & 0xC0) | (newValue & 0x3F);
  _model -> setPartyPkmnParameter(_selectedPartyIndex, parameter, value);

}
