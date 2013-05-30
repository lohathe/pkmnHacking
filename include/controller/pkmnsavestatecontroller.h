#ifndef PKMN_SAVE_STATE_CONTROLLER
#define PKMN_SAVE_STATE_CONTROLLER

#include <QObject>

#include <string>
using std::string;

class PkmnSaveStateModel;
class PkmnSaveStateView;

class PkmnPartyController;
class PkmnBoxController;
class PkmnPokedexController;

class PkmnSaveStateController : public QObject {

  Q_OBJECT

public:

  PkmnSaveStateController (string filepath);

signals:

  void operationOutcomeEvent(bool, const string &);

public slots:

  void manageSaveToFile();
  void manageOpenFile();

private:
  PkmnSaveStateModel *_model;
  PkmnSaveStateView  *_view;

  PkmnPartyController *_partyController;
  PkmnBoxController *_boxController;
  PkmnPokedexController *_pokedexController;

  void createActions();

};


#endif // PKMN_SAVE_STATE_CONTROLLER
