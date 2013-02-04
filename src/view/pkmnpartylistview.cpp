#include "pkmnpartylistview.h"
#include "pkmnspecies.h"

#include <QVBoxLayout>

PkmnPartyListView::PkmnPartyListView(QWidget *parent) : QWidget(parent) {

  QVBoxLayout *layout = new QVBoxLayout (this);

  for (int i=0; i<6; ++i) {
    _activePkmnList[i] = new PkmnPartyListItem(this, i+1);
    _activePkmnList[i] -> setSelected(false);

    QObject::connect(_activePkmnList[i], SIGNAL(pkmnSelected(int)),
                     this, SIGNAL(selectPkmnEvent(int)));

    layout -> addWidget (_activePkmnList[i]);
  }
  layout -> addStretch (1);


}

void PkmnPartyListView::setSelectedPartyPkmn(int index) {

  for (int i = 0; i < 6; ++i) {
    _activePkmnList[i] -> setSelected(false);
  }
  if (index > 0)
    _activePkmnList[index - 1] -> setSelected(true);

}

void PkmnPartyListView::updateSingleItem(const PkmnSpecies *pkmnInfo, int index) {

  if (index < 1 || index > 6) return;

  _activePkmnList[index-1] -> updateItem(pkmnInfo);

}

void PkmnPartyListView::updateWholeList (vector<const PkmnSpecies *> pkmnList) {

  for (unsigned int i=0; i<6; ++i) {
    if (i < pkmnList.size())
      _activePkmnList[i] -> updateItem(pkmnList[i]);
    else
      _activePkmnList[i] -> updateItem(PkmnSpeciesList::get(0));
  }
//  if (_selected >= pkmnList.size()) {
//    _activePkmnList[_selected] -> setSelected(false);
//    _selected = -1;
//    emit changedSelectedPkmn(_selected);
//  }

}
