#ifndef PKMN_SAVE_STATE_CONTROLLER
#define PKMN_SAVE_STATE_CONTROLLER

#include <QObject>

#include <string>
using std::string;

class PkmnSaveStateModel;
class PkmnSaveStateView;

class PkmnPartyController;
class PkmnPokedexController;

class PkmnSaveStateController : public QObject {

  Q_OBJECT

public:

  PkmnSaveStateController (string filepath);

signals:

  void operationOutcomeEvent(bool, const string &);

public slots:

  void manageSaveToFile();

private:
  PkmnSaveStateModel *_model;
  PkmnSaveStateView  *_view;

  PkmnPartyController *_partyController;
  PkmnPokedexController *_pokedexController;

};


#endif // PKMN_SAVE_STATE_CONTROLLER
