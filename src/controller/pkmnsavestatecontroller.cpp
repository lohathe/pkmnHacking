#include "pkmnsavestatecontroller.h"
#include "pkmnpartycontroller.h"
#include "pkmnpokedexcontroller.h"

#include "pkmnsavestatemodel.h"
#include "pkmnsavestate.h"

#include "pkmnsavestateview.h"

#include <string>
using std::string;

PkmnSaveStateController::PkmnSaveStateController (string filepath) {

  _model = new PkmnSaveStateModel(new PkmnSaveState(filepath, true));
  _view = new PkmnSaveStateView();

  // CREATION OF SUB-CONTROLLERS
  _partyController = new PkmnPartyController(_model, _view->getPartyView());
  connect(_partyController, SIGNAL(operationOutcomeEvent(bool,string)),
          _view,            SLOT(manageOperationOutcome(bool,string)));

  _pokedexController = new PkmnPokedexController(_model, _view->getPokedexView());
  connect(_pokedexController, SIGNAL(operationOutcomeEvent(bool,string)),
          _view,              SLOT(manageOperationOutcome(bool,string)));

  // CONNECTION BETWEEN TOTALCONTROLLER & TOTALVIEW
  connect(_view, SIGNAL(saveToFileEvent()),
          this,  SLOT(manageSaveToFile()));
  connect(this,  SIGNAL(operationOutcomeEvent(bool,string)),
          _view, SLOT(manageOperationOutcome(bool,string)));



  _view -> manageOperationOutcome(true, "Application started.");

}

void PkmnSaveStateController::manageSaveToFile() {

  bool outcome;
  // PERFORMS INTEGRITY CHECK
  outcome = _model -> saveToFile();

  if (outcome)
    emit operationOutcomeEvent(true,
                               "Changes written to file.");
  else
    emit operationOutcomeEvent(false,
                               "Some error while saving changes to file.");

}
