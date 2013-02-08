#include "pkmnpartyview.h"

#include "pkmnpartylistview.h"
#include "pkmninfoview.h"
#include "pkmnspeciespickerview.h"
#include "pkmnmovepickerview.h"

#include "pkmnsavestatemodel.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

PkmnPartyView::PkmnPartyView (QWidget *parent) :
  QWidget(parent), _selectedPartyPkmn(0), _disableUpdate(false), _model(NULL) {

  QPushButton *create = new QPushButton("CREATE", this);
  connect(create, SIGNAL(clicked()), this, SIGNAL(createPkmnEvent()));
  QPushButton *remove = new QPushButton("DELETE", this);
  connect(remove, SIGNAL(clicked()), this, SIGNAL(deletePkmnEvent()));

  _partyList = new PkmnPartyListView(this);
  connect(_partyList, SIGNAL(selectPkmnEvent(int)),
          this,       SIGNAL(partyPkmnSelectedEvent(int)));

  _pkmnInfo = new PkmnInfoView(this);
  connect(_pkmnInfo, SIGNAL(pkmnNameChangedEvent(const string &)),
          this,      SLOT(managePkmnNameChanged(const string &)));
  connect(_pkmnInfo, SIGNAL(pkmnParameterChangedEvent(int,int)),
          this,      SLOT(managePkmnParameterChanged(int,int)));
  connect(_pkmnInfo, SIGNAL(speciesChangeEvent()),
          this,      SLOT(managePkmnSpeciesChange()));
  connect(_pkmnInfo, SIGNAL(moveChangeEvent(int)),
          this,      SLOT(managePkmnMoveChange(int)));

  _speciesPicker = new PkmnSpeciesPickerView(this);
  connect(_speciesPicker, SIGNAL(speciesSelected(int)),
          this,           SIGNAL(pkmnSpeciesSelectedEvent(int)));

  _movePicker = new PkmnMovePickerView(this);
  connect(_movePicker, SIGNAL(moveSelected(int)),
          this,        SIGNAL(pkmnMoveSelectedEvent(int)));

  QVBoxLayout *leftPanel = new QVBoxLayout();
  leftPanel -> addWidget(_partyList);
  leftPanel -> addStretch(3);
  leftPanel -> addWidget(create);
  leftPanel -> addWidget(remove);

  QVBoxLayout *rightPanel = new QVBoxLayout();
  rightPanel -> addWidget(_pkmnInfo);
  rightPanel -> addWidget(_speciesPicker);
  rightPanel -> addWidget(_movePicker);

  QHBoxLayout *hlayout = new QHBoxLayout();
  hlayout -> addLayout(leftPanel, 0);
  hlayout -> addLayout(rightPanel, 1);

  QLabel *title = new QLabel("POKEMON PARY", this);
  title -> setStyleSheet("background:#000;color:#FFF;font-weight:bold;padding:3px 300px 3px 300px;");
  QVBoxLayout *layout = new QVBoxLayout();
  layout -> addWidget(title, 1, Qt::AlignHCenter);
  layout -> addLayout(hlayout);

  setLayout(layout);

  // initial display
  displayPkmnInfo();

}

void PkmnPartyView::setSelectedPartyPkmn(int partyIndex) {
  _selectedPartyPkmn = partyIndex;
  _partyList -> setSelectedPartyPkmn(_selectedPartyPkmn);

}
void PkmnPartyView::displayPkmnInfo() {

  if (_selectedPartyPkmn == 0)
    _pkmnInfo -> updateInfo (PkmnState(NULL, NULL));
  else {
    _pkmnInfo -> updateInfo (_model -> getPartyPkmnInfo(_selectedPartyPkmn));
  }

  _speciesPicker -> setVisible(false);
  _movePicker -> setVisible(false);
  _pkmnInfo -> setVisible(true);

}

void PkmnPartyView::displaySpeciesPicker() {
  _speciesPicker -> setVisible(true);
  _movePicker -> setVisible(false);
  _pkmnInfo -> setVisible(false);
}
void PkmnPartyView::displayMovePicker() {
  _speciesPicker -> setVisible(false);
  _movePicker -> setVisible(true);
  _pkmnInfo -> setVisible(false);
}

void PkmnPartyView::connectModel(PkmnSaveStateModel *model) {

  _model = model;
  connect(_model, SIGNAL(changedPkmnPartyListEvent()),
          this, SLOT(manageChangedPkmnPartyList()));
  connect(_model, SIGNAL(changedPkmnPartyInfoEvent()),
          this, SLOT(manageChangedPkmnPartyInfo()));

}

void PkmnPartyView::manageChangedPkmnPartyList() {

  _partyList -> updateWholeList(_model -> getPartyPkmnList());
  _partyList -> setSelectedPartyPkmn(_selectedPartyPkmn);

}

void PkmnPartyView::manageChangedPkmnPartyInfo() {

  _disableUpdate = true;

  _pkmnInfo -> updateInfo(_model -> getPartyPkmnInfo(_selectedPartyPkmn));

  _disableUpdate = false;

}

void PkmnPartyView::managePkmnNameChanged(const string &name) {

  if (_disableUpdate)
    return;
  emit pkmnNameChangedEvent(name);

}
void PkmnPartyView::managePkmnParameterChanged(int info, int value) {

  if (_disableUpdate)
    return;
  emit pkmnParameterChangedEvent(info, value);

}

void PkmnPartyView::managePkmnSpeciesChange() {
  if (_disableUpdate)
    return;
  emit pkmnSpeciesChangeEvent();
}

void PkmnPartyView::managePkmnMoveChange(int whichMove) {
  if (_disableUpdate)
    return;
  emit pkmnMoveChangeEvent(whichMove);
}
