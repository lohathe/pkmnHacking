#include "pkmnpokedexcontroller.h"

#include "pkmnsavestatemodel.h"
#include "pkmnspecies.h"

#include "pkmnpokedexview.h"

#include <string>
using std::string;

PkmnPokedexController::PkmnPokedexController(PkmnSaveStateModel *model,
                                             PkmnPokedexView *view) :
  _model(model), _view(view) {

  _view -> connectModel(model);

  connect(_view, SIGNAL(pkmnPokedexEntryClicked(int)),
          this, SLOT(managePkmnPokedexEntryClicked(int)));

}

void PkmnPokedexController::managePkmnPokedexEntryClicked(int pkmnIndex) {

  bool isSeen = (_model -> getPkmnPokedex()).isPkmnSeen(pkmnIndex);
  bool isCatched = (_model -> getPkmnPokedex()).isPkmnCatched(pkmnIndex);
  string pkmn = PkmnSpeciesList::getByIndex(pkmnIndex)->getName();

  if (isCatched) {
    _model -> setPkmnPokedexSeen(pkmnIndex, false);
    _model -> setPkmnPokedexCatched(pkmnIndex, false);

    emit operationOutcomeEvent(true, pkmn +" is now unknown.");
  } else if (isSeen) {
    _model -> setPkmnPokedexCatched(pkmnIndex, true);

    emit operationOutcomeEvent(true, pkmn +" is now catched.");
  } else {
    _model -> setPkmnPokedexSeen(pkmnIndex, true);

    emit operationOutcomeEvent(true, pkmn +" is now seen.");
  }

}
