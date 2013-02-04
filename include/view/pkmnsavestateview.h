#ifndef PKMN_SAVE_STATE_VIEW
#define PKMN_SAVE_STATE_VIEW

#include <QMainWindow>

class PkmnPartyView;
class PkmnSaveStateModel;

class PkmnSaveStateView : public QMainWindow {

public:
  PkmnSaveStateView ();

  PkmnPartyView *getPartyView();

private:
  PkmnPartyView *_partyView;

};

#endif // PKMN_SAVE_STATE_VIEW
