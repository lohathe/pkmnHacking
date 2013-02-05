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

PkmnElementPickerView::PkmnElementPickerView(QWidget *parent) :
  QMenu("Sort by element", parent) {

  PkmnElementPickerAction *elements[16];
  elements[0]  = new PkmnElementPickerAction(this, 0xFF);
  elements[1]  = new PkmnElementPickerAction(this, Element::NORMAL);
  elements[2]  = new PkmnElementPickerAction(this, Element::FIGHTING);
  elements[3]  = new PkmnElementPickerAction(this, Element::FLYING);
  elements[4]  = new PkmnElementPickerAction(this, Element::POISON);
  elements[5]  = new PkmnElementPickerAction(this, Element::GROUND);
  elements[6]  = new PkmnElementPickerAction(this, Element::ROCK);
  elements[7]  = new PkmnElementPickerAction(this, Element::BUG);
  elements[8]  = new PkmnElementPickerAction(this, Element::GHOST);
  elements[9]  = new PkmnElementPickerAction(this, Element::FIRE);
  elements[10] = new PkmnElementPickerAction(this, Element::WATER);
  elements[11] = new PkmnElementPickerAction(this, Element::GRASS);
  elements[12] = new PkmnElementPickerAction(this, Element::ELECTRIC);
  elements[13] = new PkmnElementPickerAction(this, Element::PSYCHIC);
  elements[14] = new PkmnElementPickerAction(this, Element::ICE);
  elements[15] = new PkmnElementPickerAction(this, Element::DRAGON);

  for (int i=0; i<16; ++i) {
    addAction (elements[i]);
    connect(elements[i], SIGNAL(elementActionTriggered(int)),
            this,        SIGNAL(elementSelected(int)));
  }

}


int PkmnElementPickerView::getSelectedElement() const {

  PkmnElementPickerAction *action = dynamic_cast<PkmnElementPickerAction *>(activeAction());
  if (action == NULL)
    return 0xFF;

  return action->getElement();

}
