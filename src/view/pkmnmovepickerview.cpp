#include "pkmnmovepickerview.h"
#include "pkmnmove.h"
#include "pkmnelement.h"

#include <vector>

#include <QObject>
#include <QString>
#include <QButtonGroup>
#include <QScrollArea>

PkmnMovePickerView::PkmnMovePickerView(QWidget *parent) :
  QWidget(parent), _whichMove(0) {

  QButtonGroup *buttonGroup = new QButtonGroup(this);
  QWidget *listWidget = new QWidget(this);
  _layout = new QVBoxLayout(listWidget);

  for (int i=0; i<166; ++i) {
    const PkmnMove *move = PkmnMoveList::get(i);
    _moveList[i] = new QPushButton(QString::fromStdString(move->getName()), this);

    buttonGroup -> addButton (_moveList[i], move->getId());
    _layout -> addWidget(_moveList[i], 1);
  }
  listWidget -> setLayout(_layout);

  QScrollArea *scrollArea = new QScrollArea(this);
  scrollArea -> setWidget(listWidget);
  scrollArea -> setWidgetResizable(true);

  //selectByElement(0xFF);

  QObject::connect(buttonGroup, SIGNAL(buttonClicked(int)),
                   this, SLOT(manageButtonClicked(int)));

  QPushButton *elementSelect = new QPushButton("Select move element");
  QObject::connect(elementSelect, SIGNAL(clicked()),
                   this, SLOT(foo()));

  QVBoxLayout *vlayout = new QVBoxLayout(this);
  vlayout -> addWidget(elementSelect);
  vlayout -> addWidget(scrollArea);

  setLayout(vlayout);

}

void PkmnMovePickerView::foo () {
  for (int i=0; i<166; i++)
    _moveList[i] -> setVisible(false);
  std::vector<const PkmnMove *> list = PkmnMoveList::getByElement(Element::FIRE);
  for (unsigned int i=0; i<list.size(); ++i)
    _moveList[list[i]->getId()] -> setVisible(true);
}

void PkmnMovePickerView::setChangingMove(int whichMove) {
  _whichMove = whichMove;
}
void PkmnMovePickerView::manageButtonClicked(int value) {
  emit moveSelected(_whichMove, value);
}
