#ifndef PKMN_BOX_VIEW
#define PKMN_BOX_VIEW

#include <QWidget>

#include <string>
using std::string;

#include "pkmninfoview.h"
#include "pkmnspeciespickerview.h"
#include "pkmnmovepickerview.h"
#include "pkmnlistview.h"

class PkmnSaveStateModel;

class PkmnBoxView : public QWidget {

  Q_OBJECT

public:

  PkmnBoxView (QWidget *);

  void connectModel(PkmnSaveStateModel *);

  void setSelectedBox(int);
  void setSelectedBoxPkmn(int);
  void displayPkmnInfo();
  void displaySpeciesPicker();
  void displayMovePicker();

  void setCoherencyEnabled(bool);

signals:

  void boxSelectedEvent(int);
  void boxPkmnSelectedEvent(int);

public slots:


private:

  int _selectedBoxIndex;
  int _selectedPkmnIndex;
  bool _disableUpdate;

  PkmnSaveStateModel *_model;

  PkmnInfoView *_pkmnInfo;
  PkmnSpeciesPickerView *_speciesPicker;
  PkmnMovePickerView *_movePicker;
  PkmnListView *_pkmnList;

};

#endif // PKMN_BOX_VIEW
