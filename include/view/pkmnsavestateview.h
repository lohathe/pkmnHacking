#ifndef PKMN_SAVE_STATE_VIEW
#define PKMN_SAVE_STATE_VIEW

#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>

#include <string>
using std::string;

class PkmnPartyView;
class PkmnPokedexView;

class PkmnSaveStateModel;

class PkmnSaveStateView : public QMainWindow {

  Q_OBJECT

public:

  PkmnSaveStateView ();

  PkmnPartyView *getPartyView();
  PkmnPokedexView *getPokedexView();

signals:
  void saveToFileEvent();

public slots:
  void manageOperationOutcome(bool, const string &);

private slots:


private:

  PkmnPartyView *_partyView;
  PkmnPokedexView *_pokedexView;

  QToolBar *_toolBar;
  QStatusBar *_statusBar;
  QLabel *_statusMessage;
  QLabel *_statusImg;

  // UTILITY FUNCTIONS
  void createMyToolBar();
  void createMyStatusBar();

};

#endif // PKMN_SAVE_STATE_VIEW
