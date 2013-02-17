#include "pkmnelementpickerview.h"
#include "pkmnelement.h"

PkmnElementPickerAction::PkmnElementPickerAction (QObject *parent, int value)
  : QAction(parent), _elementValue(value) {

  if (value == 0xFF)
    setText("All elements");
  else
    setText (QString::fromStdString(Element::toString(value)));

  connect(this, SIGNAL(triggered()), this, SLOT(manageTriggered()));

}
int PkmnElementPickerAction::getElement() const {
  return _elementValue;
}

void PkmnElementPickerAction::manageTriggered() {
  emit elementActionTriggered(_elementValue);
}

PkmnElementPickerView::PkmnElementPickerView(QWidget *parent, bool allElements) :
  QMenu("Sort by element", parent) {

  PkmnElementPickerAction *elements[15];
  PkmnElementPickerAction *allElementAction;

  elements[0]  = new PkmnElementPickerAction(this, Element::NORMAL);
  elements[1]  = new PkmnElementPickerAction(this, Element::FIGHTING);
  elements[2]  = new PkmnElementPickerAction(this, Element::FLYING);
  elements[3]  = new PkmnElementPickerAction(this, Element::POISON);
  elements[4]  = new PkmnElementPickerAction(this, Element::GROUND);
  elements[5]  = new PkmnElementPickerAction(this, Element::ROCK);
  elements[6]  = new PkmnElementPickerAction(this, Element::BUG);
  elements[7]  = new PkmnElementPickerAction(this, Element::GHOST);
  elements[8]  = new PkmnElementPickerAction(this, Element::FIRE);
  elements[9]  = new PkmnElementPickerAction(this, Element::WATER);
  elements[10] = new PkmnElementPickerAction(this, Element::GRASS);
  elements[11] = new PkmnElementPickerAction(this, Element::ELECTRIC);
  elements[12] = new PkmnElementPickerAction(this, Element::PSYCHIC);
  elements[13] = new PkmnElementPickerAction(this, Element::ICE);
  elements[14] = new PkmnElementPickerAction(this, Element::DRAGON);

  if (allElements) {
    allElementAction = new PkmnElementPickerAction(this, 0xFF);
    addAction(allElementAction);
    connect(allElementAction, SIGNAL(elementActionTriggered(int)),
            this,             SIGNAL(elementSelected(int)));
  }

  for (int i=0; i<15; ++i) {
    addAction (elements[i]);
    connect(elements[i], SIGNAL(elementActionTriggered(int)),
            this,        SIGNAL(elementSelected(int)));
  }

}

PkmnElementComboBox::PkmnElementComboBox(QWidget *parent, int referredInfo)
  : QComboBox(parent), _referredInfo(referredInfo) {

  insertItem( 0, QString::fromStdString(Element::toString(Element::NORMAL)));
  insertItem( 1, QString::fromStdString(Element::toString(Element::FIGHTING)));
  insertItem( 2, QString::fromStdString(Element::toString(Element::FLYING)));
  insertItem( 3, QString::fromStdString(Element::toString(Element::POISON)));
  insertItem( 4, QString::fromStdString(Element::toString(Element::GROUND)));
  insertItem( 5, QString::fromStdString(Element::toString(Element::ROCK)));
  insertItem( 6, QString::fromStdString(Element::toString(Element::BUG)));
  insertItem( 7, QString::fromStdString(Element::toString(Element::GHOST)));
  insertItem( 8, QString::fromStdString(Element::toString(Element::FIRE)));
  insertItem( 9, QString::fromStdString(Element::toString(Element::WATER)));
  insertItem(10, QString::fromStdString(Element::toString(Element::GRASS)));
  insertItem(11, QString::fromStdString(Element::toString(Element::ELECTRIC)));
  insertItem(12, QString::fromStdString(Element::toString(Element::PSYCHIC)));
  insertItem(13, QString::fromStdString(Element::toString(Element::ICE)));
  insertItem(14, QString::fromStdString(Element::toString(Element::DRAGON)));

  connect(this, SIGNAL(activated(int)), this, SLOT(manageSelection(int)));

}

void PkmnElementComboBox::manageSelection(int selectedElement) {
  emit elementSelected(_referredInfo, getElementIdFromIndex(selectedElement));
}
int PkmnElementComboBox::getSelectedElement() const {
  return getElementIdFromIndex(currentIndex());
}
void PkmnElementComboBox::setSelectedElement(int selectedElement) {
  if (currentIndex() == getElementIndexFromId(selectedElement))
    return;
  setCurrentIndex(getElementIndexFromId(selectedElement));
}

int PkmnElementComboBox::getElementIdFromIndex(int index) const {
  int elementId = 0;
  switch (index) {
    case  0: elementId = Element::NORMAL; break;
    case  1: elementId = Element::FIGHTING; break;
    case  2: elementId = Element::FLYING; break;
    case  3: elementId = Element::POISON; break;
    case  4: elementId = Element::GROUND; break;
    case  5: elementId = Element::ROCK; break;
    case  6: elementId = Element::BUG; break;
    case  7: elementId = Element::GHOST; break;
    case  8: elementId = Element::FIRE; break;
    case  9: elementId = Element::WATER; break;
    case 10: elementId = Element::GRASS; break;
    case 11: elementId = Element::ELECTRIC; break;
    case 12: elementId = Element::PSYCHIC; break;
    case 13: elementId = Element::ICE; break;
    case 14: elementId = Element::DRAGON; break;
  }
  return elementId;
}
int PkmnElementComboBox::getElementIndexFromId(int id) const {
  int elementIndex = 0;
  switch (id) {
    case Element::NORMAL   : elementIndex =  0; break;
    case Element::FIGHTING : elementIndex =  1; break;
    case Element::FLYING   : elementIndex =  2; break;
    case Element::POISON   : elementIndex =  3; break;
    case Element::GROUND   : elementIndex =  4; break;
    case Element::ROCK     : elementIndex =  5; break;
    case Element::BUG      : elementIndex =  6; break;
    case Element::GHOST    : elementIndex =  7; break;
    case Element::FIRE     : elementIndex =  8; break;
    case Element::WATER    : elementIndex =  9; break;
    case Element::GRASS    : elementIndex = 10; break;
    case Element::ELECTRIC : elementIndex = 11; break;
    case Element::PSYCHIC  : elementIndex = 12; break;
    case Element::ICE      : elementIndex = 13; break;
    case Element::DRAGON   : elementIndex = 14; break;
  }
  return elementIndex;
}
