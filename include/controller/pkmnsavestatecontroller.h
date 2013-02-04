#ifndef PKMN_SAVE_STATE_CONTROLLER
#define PKMN_SAVE_STATE_CONTROLLER

#include <QObject>

#include <string>
using std::string;

class PkmnSaveStateModel;
class PkmnSaveStateView;
class PkmnPartyController;

class PkmnSaveStateController : public QObject {

  Q_OBJECT

public:
  PkmnSaveStateController (string filepath);

private:
  PkmnSaveStateModel *_model;
  PkmnSaveStateView  *_view;

  PkmnPartyController *_partyController;

};


#endif // PKMN_SAVE_STATE_CONTROLLER
