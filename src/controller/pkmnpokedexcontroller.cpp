#include "pkmnpokedexcontroller.h"

#include "pkmnsavestatemodel.h"

#include "pkmnpokedexview.h"

PkmnPokedexController::PkmnPokedexController(PkmnSaveStateModel *model,
                                             PkmnPokedexView *view) :
  _model(model), _view(view) {

  _view -> connectModel(model);

}

void PkmnPokedexController::managePkmnPokedexEntryChanged(int pkmnIndex, int status) {

  pkmnIndex = 0;
  status = 0;

}
