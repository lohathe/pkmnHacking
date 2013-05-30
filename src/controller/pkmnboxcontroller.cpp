#include "pkmnboxcontroller.h"
#include "pkmnsavestatemodel.h"
#include "pkmnboxview.h"

PkmnBoxController::PkmnBoxController (PkmnSaveStateModel *model,
                                      PkmnBoxView *view)
  : _model(model),
    _view(view),
    _selectedBoxIndex(0),
    _selectedPkmnIndex(0),
    _selectedMoveIndex(0),
    _isCreatingPkmn(false),
    _isChangingMove(false) {

  connect (_view, SIGNAL(boxPkmnSelectedEvent(int)),
           this,  SLOT(manageBoxPkmnSelected(int)));
  connect (_view, SIGNAL(boxSelectedEvent(int)),
           this,  SLOT(manageBoxSelected(int)));

  _view -> connectModel(_model);

}

void PkmnBoxController::manageBoxSelected(int boxIndex) {

  if (boxIndex < 1 || boxIndex > 12) {
    emit operationOutcome(false,
                          "No valid box selected.");
    return;
  }

  _selectedBoxIndex = boxIndex;
  _selectedPkmnIndex = 0;
  _selectedMoveIndex = 0;
  _isCreatingPkmn = 0;
  _isChangingMove = 0;

  _view -> setSelectedBox(_selectedBoxIndex);
  _view -> setSelectedBoxPkmn(_selectedPkmnIndex);
  _view -> displayPkmnInfo();

}
void PkmnBoxController::manageBoxPkmnSelected(int pkmnIndex) {

  if (pkmnIndex < 0 ||
      pkmnIndex > 20 ||
      _selectedBoxIndex == 0 ||
      pkmnIndex > _model->getBoxPkmnCount(_selectedBoxIndex)) {
    emit operationOutcome(false,
                          "No valid pokemon in box selected.");
    return;
  }

  _selectedPkmnIndex = pkmnIndex;
  _selectedMoveIndex = 0;
  _isCreatingPkmn = 0;
  _isChangingMove = 0;

  //_view -> setSelectedBox(_selectedBoxIndex);
  _view -> setSelectedBoxPkmn(_selectedPkmnIndex);
  _view -> displayPkmnInfo();

}

void PkmnBoxController::manageCreatePkmn() {
/*
  if (_model -> getBoxPkmnCount(_selectedBoxIndex) >= 6) {
    emit operationOutcomeEvent(false,
                               "Cannot have more than 6 pokemon in party.");
    return;
  }

  _isCreatingPkmn = true;
  _isChangingMove = false;

  _view -> displaySpeciesPicker();
*/
}

void PkmnBoxController::manageDeletePkmn() {}
void PkmnBoxController::manageDeleteBox() {}
void PkmnBoxController::manageSpeciesChange() {}
void PkmnBoxController::manageMoveChange(int) {}

void PkmnBoxController::managePkmnSpeciesSelected(int) {}
void PkmnBoxController::managePkmnMoveSelected(int) {}
void PkmnBoxController::managePkmnStrParamChanged(int, const string &) {}
void PkmnBoxController::managePkmnParameterChanged(int, int) {}
