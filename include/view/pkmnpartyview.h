#ifndef PKMN_PARTY_VIEW
#define PKMN_PARTY_VIEW

#include <string>
using std::string;

#include <QWidget>

#include "pkmnspeciespickerview.h"
#include "pkmnmovepickerview.h"
#include "pkmnpartylistview.h"
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

signals:

  void partyPkmnSelectedEvent(int);

  void createPkmnEvent();
  void deletePkmnEvent();

  void pkmnSpeciesChangeEvent();
  void pkmnSpeciesSelectedEvent(int);
  void pkmnMoveChangeEvent(int);
  void pkmnMoveSelectedEvent(int);
  void pkmnNameChangedEvent(const string &);
  void pkmnParameterChangedEvent(int, int);

public slots:

  void manageChangedPkmnPartyList();
  void manageChangedPkmnPartyInfo();
  void managePkmnNameChanged(const string &);
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
