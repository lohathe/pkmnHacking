#include "pkmnmovepickerview.h"
#include "pkmnmove.h"
#include "pkmnelement.h"

#include <vector>
using std::vector;
#include <algorithm>

#include <QObject>
#include <QString>
#include <QButtonGroup>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

PkmnMovePickerView::PkmnMovePickerView(QWidget *parent) :
  QWidget(parent), _element(0xFF), _sorting(0) {

  QPushButton *elementSelect = new QPushButton("Filter by element");
  _elementPicker = new PkmnElementPickerView(this);
  connect(_elementPicker, SIGNAL(elementSelected(int)),
          this,           SLOT(manageFilter(int)));
  elementSelect->setMenu(_elementPicker);

  _order[0] = new QRadioButton("Name", this);
  _order[1] = new QRadioButton("Power", this);
  //_order[0] = new QRadioButton("PP", this);
  //_order[0] = new QRadioButton("Acc", this);
  _order[0] -> setChecked(true);
  QButtonGroup *sortGroup = new QButtonGroup(this);
  sortGroup -> addButton(_order[0], 0);
  sortGroup -> addButton(_order[1], 1);
  connect(sortGroup, SIGNAL(buttonClicked(int)),
          this,      SLOT(manageSort(int)));

  QHBoxLayout *sortFilterLayout = new QHBoxLayout();
  sortFilterLayout -> addWidget(elementSelect, 3);
  sortFilterLayout -> addWidget(new QLabel("Sort by:", this), 1);
  sortFilterLayout -> addWidget(_order[0], 1);
  sortFilterLayout -> addWidget(_order[1], 1);

  QWidget *listWidget = new QWidget(this);
  _layout = new QGridLayout(listWidget);

  for (int i=0; i<166; ++i) {
    _moveList[i] = new PkmnMoveListItem(listWidget, i);
    connect(_moveList[i], SIGNAL(moveSelected(int)),
            this, SIGNAL(moveSelected(int)));
    _layout -> setRowStretch(i, 1);
//    layout -> addWidget(_moveList[i], 1);
  }
  manageSortOrFilter();
//  layout -> addStretch(1);
  listWidget -> setLayout(_layout);

  QScrollArea *scrollArea = new QScrollArea(this);
  scrollArea -> setWidget(listWidget);
  scrollArea -> setWidgetResizable(true);

//  connect(buttonGroup, SIGNAL(buttonClicked(int)),
//          this,        SLOT(manageButtonClicked(int)));

  QVBoxLayout *vlayout = new QVBoxLayout(this);
  vlayout -> addLayout(sortFilterLayout);
  vlayout -> addWidget(scrollArea);

  setLayout(vlayout);

}

void PkmnMovePickerView::manageFilter(int value) {
  _element = value;
  manageSortOrFilter();
}

void PkmnMovePickerView::manageSort(int value) {
  _sorting = value;
  manageSortOrFilter();
}

bool compareByName (const PkmnMove *m1, const PkmnMove *m2) {
  return (m1->getName() < m2->getName());
}
bool compareByPwr (const PkmnMove *m1, const PkmnMove *m2) {
  return (m1->getPwr() < m2->getPwr());
}
void PkmnMovePickerView::manageSortOrFilter() {

  for (int i=0; i<166; i++)
    _moveList[i] -> setVisible(false);

  vector<const PkmnMove *> list;
  if (_element == 0xFF)
    list = PkmnMoveList::getWholeList();
  else
    list = PkmnMoveList::getByElement(_element);

  if (_sorting == 0) {
    std::sort(list.begin(), list.end(), compareByName);
  } else if (_sorting == 1) {
    std::sort(list.begin(), list.end(), compareByPwr);
  }

  for (unsigned int i=0; i<list.size(); ++i) {
    _moveList[list[i]->getId()] -> setIndex(i);
    _layout -> addWidget(_moveList[list[i]->getId()], i, 0);
    _moveList[list[i]->getId()] -> setVisible(true);
  }

}
/*
void PkmnMovePickerView::foo () {
  for (int i=0; i<166; i++)
    _moveList[i] -> setVisible(false);
  std::vector<const PkmnMove *> list = PkmnMoveList::getByElement(Element::FIRE);
  for (unsigned int i=0; i<list.size(); ++i)
    _moveList[list[i]->getId()] -> setVisible(true);
}*/

void PkmnMovePickerView::manageButtonClicked(int value) {
  emit moveSelected(value);
}
