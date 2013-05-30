#include "pkmnboxview.h"

#include "pkmnsavestatemodel.h"

PkmnBoxView::PkmnBoxView (QWidget *parent) :
  QWidget(parent),
  _selectedBoxIndex(0),
  _selectedPkmnIndex(0),
  _disableUpdate(false),
  _model(NULL) {

  // List of the pokemon stored in the selected box
  _pkmnList = new PkmnListViewSmallIcon(this, 20, 2, Qt::Horizontal);
  connect (_pkmnList, SIGNAL(selectPkmnEvent(int)),
           this,      SIGNAL(boxPkmnSelectedEvent(int)));

  // Visual displayer for the info of the selected pokemon
  _pkmnInfo = new PkmnInfoViewBox(this);
  //// CONNECT USER INTERACTION

  QSpinBox *temp = new QSpinBox(this);
  temp -> setMinimum(0);
  temp -> setMaximum(20);
  connect (temp, SIGNAL(valueChanged(int)),
           this, SIGNAL(boxSelectedEvent(int)));

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(temp);
  layout->addWidget(_pkmnList);
  layout->addWidget(_pkmnInfo);

  setLayout(layout);

  displayPkmnInfo();

}

void PkmnBoxView::connectModel(PkmnSaveStateModel *model) {

  _model = model;
//  connect(_model, SIGNAL(changedPkmnBoxListEvent()),
//          this, SLOT(manageChangedPkmnBoxList()));
//  connect(_model, SIGNAL(changedPkmnBoxInfoEvent()),
//          this, SLOT(manageChangedPkmnBoxInfo()));

}

void PkmnBoxView::setSelectedBox(int boxIndex) {
  _selectedBoxIndex = boxIndex;
  if (_selectedBoxIndex == 0) {
    vector<const PkmnSpecies*> emptyList;
    //for (int i=0; i<20; i++) emptyList.push_back(PkmnSpeciesList::getById(0));
    _pkmnList -> updateWholeList(emptyList);
  } else {
    _pkmnList -> updateWholeList(_model -> getBoxPkmnList(_selectedBoxIndex));
  }
  _pkmnInfo -> updateInfo (PkmnState(NULL, NULL, NULL));
}

void PkmnBoxView::setSelectedBoxPkmn(int pkmnIndex) {
  _selectedPkmnIndex = pkmnIndex;
  _pkmnList -> setSelectedPartyPkmn(pkmnIndex);
}

void PkmnBoxView::displayPkmnInfo() {

  if (_selectedPkmnIndex == 0 || _selectedBoxIndex == 0)
    _pkmnInfo -> updateInfo (PkmnState(NULL, NULL, NULL));
  else {
    _disableUpdate = true;
    _pkmnInfo -> updateInfo (_model -> getBoxPkmnState (_selectedBoxIndex, _selectedPkmnIndex));
    _disableUpdate = false;
  }

}
void PkmnBoxView::displaySpeciesPicker() {}
void PkmnBoxView::displayMovePicker() {}

void PkmnBoxView::setCoherencyEnabled(bool) {}
