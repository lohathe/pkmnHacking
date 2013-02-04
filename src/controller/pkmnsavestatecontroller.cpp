#include "pkmnsavestatecontroller.h"
#include "pkmnpartycontroller.h"

#include "pkmnsavestatemodel.h"
#include "pkmnsavestate.h"

#include "pkmnsavestateview.h"

PkmnSaveStateController::PkmnSaveStateController (string filepath) {

  _model = new PkmnSaveStateModel(new PkmnSaveState(filepath, true));
  _view = new PkmnSaveStateView();

  // CONNECTION BETWEEN TOTALCONTROLLER & TOTALVIEW

  // CREATION OF SUB-CONTROLLERS
  _partyController = new PkmnPartyController(_model, _view->getPartyView());

}
