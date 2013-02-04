#include "pkmnspeciespickerview.h"
#include "pkmnspecies.h"
#include "pkmnelement.h"

#include <QPushButton>
#include <QToolButton>
#include <QButtonGroup>
#include <QScrollArea>
#include <QString>
#include <QWidget>
#include <QObject>

#include <vector>

PkmnElementSelectorAction::PkmnElementSelectorAction (QObject *parent, int value)
  : QAction(parent), _elementValue(value) {
  if (value == 0xFF)
    setText("All elements");
  else
    setText (QString::fromStdString(Element::toString(value)));
  QObject::connect(this, SIGNAL(triggered()), this, SLOT(manageTriggered()));
}
void PkmnElementSelectorAction::manageTriggered() {
  emit elementActionTriggered(_elementValue);
}

PkmnSpeciesPickerView::PkmnSpeciesPickerView (QWidget *parent) : QWidget(parent) {

  int scale = 1, imgDim = 56;

  QButtonGroup *buttonGroup = new QButtonGroup(this);
  QWidget *gridWidget = new QWidget(this);
  _layout = new QGridLayout(gridWidget);
  for (int i=0; i<5; i++) _layout -> setColumnStretch(i, 1);
  for (int i=0; i<31; i++) _layout -> setRowStretch(i, 1);

  for (int i=0; i<151; ++i) {
    const PkmnSpecies *actualPkmn = PkmnSpeciesList::getBy(PkmnSpeciesList::INDEX, i+1)[0];
    _pkmns[i] = new QToolButton(gridWidget);
    _pkmns[i] -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    _pkmns[i] -> setIcon(QPixmap(":/img/spritesyellowcolor.png")
        .copy(1+(i%12)*(imgDim+1), 1+(i/12)*(imgDim+1), imgDim, imgDim)
        .scaled(scale*imgDim, scale*imgDim));
    _pkmns[i] -> setText(QString::fromStdString(actualPkmn->getName()));
    _pkmns[i] -> setIconSize(QSize(scale*imgDim, scale*imgDim));
    _pkmns[i] -> setFixedSize(95, 85);

    buttonGroup -> addButton (_pkmns[i], actualPkmn->getId());
  }
  gridWidget -> setLayout(_layout);

  QScrollArea *scrollArea = new QScrollArea(this);
  scrollArea -> setWidget(gridWidget);
  scrollArea -> setWidgetResizable(true);

  selectByElement(0xFF);

  QObject::connect(buttonGroup, SIGNAL(buttonClicked(int)),
                   this, SIGNAL(speciesSelected(int)));

  QPushButton *elementSelect = new QPushButton("Select pokemon element");
  QMenu *elementMenu = createElementMenu();
  elementSelect->setMenu(elementMenu);

  QVBoxLayout *vlayout = new QVBoxLayout(this);
  vlayout -> addWidget(elementSelect);
  vlayout -> addWidget(scrollArea);
  //vlayout -> addStretch(1);

  setLayout(vlayout);
}

QMenu *PkmnSpeciesPickerView::createElementMenu() {

  QMenu *result = new QMenu("Select pokemon element", this);
  PkmnElementSelectorAction *elements[16];
  elements[0]  = new PkmnElementSelectorAction(result, 0xFF);
  elements[1]  = new PkmnElementSelectorAction(result, Element::NORMAL);
  elements[2]  = new PkmnElementSelectorAction(result, Element::FIGHTING);
  elements[3]  = new PkmnElementSelectorAction(result, Element::FLYING);
  elements[4]  = new PkmnElementSelectorAction(result, Element::POISON);
  elements[5]  = new PkmnElementSelectorAction(result, Element::GROUND);
  elements[6]  = new PkmnElementSelectorAction(result, Element::ROCK);
  elements[7]  = new PkmnElementSelectorAction(result, Element::BUG);
  elements[8]  = new PkmnElementSelectorAction(result, Element::GHOST);
  elements[9]  = new PkmnElementSelectorAction(result, Element::FIRE);
  elements[10] = new PkmnElementSelectorAction(result, Element::WATER);
  elements[11] = new PkmnElementSelectorAction(result, Element::GRASS);
  elements[12] = new PkmnElementSelectorAction(result, Element::ELECTRIC);
  elements[13] = new PkmnElementSelectorAction(result, Element::PSYCHIC);
  elements[14] = new PkmnElementSelectorAction(result, Element::ICE);
  elements[15] = new PkmnElementSelectorAction(result, Element::DRAGON);

  for (int i=0; i<16; ++i) {
    result -> addAction (elements[i]);
    QObject::connect(elements[i], SIGNAL(elementActionTriggered(int)),
                     this, SLOT(selectByElement(int)));
  }
  return result;
}

void PkmnSpeciesPickerView::selectByElement (int element) {
  for (int i=0; i<151; ++i) {
    //_layout -> removeWidget(_pkmns[i]);
    _pkmns[i] -> setVisible(false);
  }
  if (element == 0xFF) {
    for (int i=0; i<151; ++i) {
      _layout -> addWidget(_pkmns[i], i/5, i%5);
      //_pkmns[i] -> setGeometry(QRect(5+100*(i%5), 5+90*(i/5), 95, 85));
      _pkmns[i] -> setVisible(true);
    }
  } else {
    std::vector<const PkmnSpecies *> list = PkmnSpeciesList::getBy(PkmnSpeciesList::ELEMENT, element);
    for (unsigned int i=0; i<list.size(); i++) {
      _layout -> addWidget(_pkmns[list[i]->getIndex()-1], i/5, i%5);
      //_pkmns[i] -> setGeometry(QRect(5+100*(i%5), 5+90*(i/5), 95, 85));
      _pkmns[list[i]->getIndex()-1] -> setVisible(true);
    }
  }
}
