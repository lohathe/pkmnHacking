#include "pkmnlistview.h"
#include "pkmnspecies.h"

#include <QVBoxLayout>

PkmnListView::PkmnListView(QWidget *parent)
  : QWidget(parent) { }

void PkmnListView::initialize(
    int orientation,
    int lineNumber) {

  QGridLayout *layout = new QGridLayout(this);
  //layout -> addStretch(1);
  int max = _activePkmnList.size();
  int lineSize = max/lineNumber;
  for (int i=0; i<max; ++i) {

    int x = i/lineSize;
    int y = i%lineSize;
    if (orientation == Qt::Horizontal)
      layout -> addWidget(_activePkmnList[i], x, y, 1, 1);
    else
      layout -> addWidget(_activePkmnList[i], y, x, 1, 1);

  }
  //layout -> addStretch (1);

}

void PkmnListView::setSelectedPartyPkmn(int index) {

  for (int i = 0; i < (int)_activePkmnList.size(); ++i) {
    _activePkmnList[i] -> setSelected(false);
  }
  if (index > 0)
    _activePkmnList[index - 1] -> setSelected(true);

}

void PkmnListView::updateSingleItem(const PkmnSpecies *pkmnInfo, int index) {

  if (index < 1 || index > (int)_activePkmnList.size()) return;

  _activePkmnList[index-1] -> updateItem(pkmnInfo);

}

void PkmnListView::updateWholeList (vector<const PkmnSpecies *> pkmnList) {

  for (unsigned int i=0; i< (int)_activePkmnList.size(); ++i) {
    if (i < pkmnList.size())
      _activePkmnList[i] -> updateItem(pkmnList[i]);
    else
      _activePkmnList[i] -> updateItem(PkmnSpeciesList::getById(0));
  }
//  if (_selected >= pkmnList.size()) {
//    _activePkmnList[_selected] -> setSelected(false);
//    _selected = -1;
//    emit changedSelectedPkmn(_selected);
//  }

}

// LARGE ICONS

PkmnListViewLargeIcon::PkmnListViewLargeIcon (
    QWidget *parent,
    int elementNumber,
    int lineNumber,
    int orientation)
  : PkmnListView(parent) {

  _activePkmnList.resize(elementNumber);

  for (int i=0; i<elementNumber; ++i) {

    _activePkmnList[i] = new PkmnSpeciesListItemLarge(this, i+1);
    _activePkmnList[i] -> setSelected(false);

    connect(_activePkmnList[i], SIGNAL(pkmnSelected(int)),
            this, SIGNAL(selectPkmnEvent(int)));

  }

  initialize(orientation, lineNumber);

}

// SMALL ICONS

PkmnListViewSmallIcon::PkmnListViewSmallIcon (
    QWidget *parent,
    int elementNumber,
    int lineNumber,
    int orientation)
  : PkmnListView(parent) {

  _activePkmnList.resize(elementNumber);

  for (int i=0; i<elementNumber; ++i) {

    _activePkmnList[i] = new PkmnSpeciesListItemSmall(this, i+1);
    _activePkmnList[i] -> setSelected(false);

    connect(_activePkmnList[i], SIGNAL(pkmnSelected(int)),
            this, SIGNAL(selectPkmnEvent(int)));

  }

  initialize(orientation, lineNumber);

}
