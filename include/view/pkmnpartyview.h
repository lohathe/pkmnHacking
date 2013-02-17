#ifndef PKMN_PARTY_VIEW
#define PKMN_PARTY_VIEW

#include <QWidget>

#include <string>
using std::string;

#include "pkmnspeciespickerview.h"
#include "pkmnmovepickerview.h"
#include "pkmnlistview.h"
#include "pkmninfoview.h"

class PkmnSaveStateModel;

class PkmnPartyView : public QWidget {

  Q_OBJECT

public:

  PkmnPartyView(QWidget *);

  void connectModel(PkmnSaveStateModel *);

  void setSelectedPartyPkmn(int);
  void displayPkmnInfo();
  void displaySpeciesPicker();
  void displayMovePicker();

  void setCoherencyEnabled(bool);

signals:

  void partyPkmnSelectedEvent(int);

  void createPkmnEvent();
  void deletePkmnEvent();

  void pkmnSpeciesChangeEvent();
  void pkmnSpeciesSelectedEvent(int);
  void pkmnMoveChangeEvent(int);
  void pkmnMoveSelectedEvent(int);
  void pkmnStrParamChangedEvent(int, const string &);
  void pkmnParameterChangedEvent(int, int);

public slots:

  void manageChangedPkmnPartyList();
  void manageChangedPkmnPartyInfo();
  void managePkmnStrParamChanged(int, const string &);
  void managePkmnParameterChanged(int, int);
  void managePkmnSpeciesChange();
  void managePkmnMoveChange(int);


private:

  int _selectedPartyPkmn;
  bool _disableUpdate;
  PkmnSaveStateModel *_model;

  PkmnInfoView *_pkmnInfo;
  PkmnSpeciesPickerView *_speciesPicker;
  PkmnMovePickerView *_movePicker;
  PkmnPartyListView *_partyList;

};

#endif // PKMN_PARTY_VIEW
