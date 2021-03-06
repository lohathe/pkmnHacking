#include "pkmnspeciespickerview.h"
#include "pkmnspecies.h"
#include "pkmnelementpickerview.h"

#include <QPushButton>
#include <QToolButton>
#include <QButtonGroup>
#include <QScrollArea>
#include <QString>
#include <QWidget>
#include <QObject>

#include <vector>

PkmnSpeciesPickerView::PkmnSpeciesPickerView (QWidget *parent) : QWidget(parent) {

  int scale = 1, imgDim = 56;

  QButtonGroup *buttonGroup = new QButtonGroup(this);
  QWidget *gridWidget = new QWidget(this);
  _layout = new QGridLayout(gridWidget);
  for (int i=0; i<5; i++) _layout -> setColumnStretch(i, 1);
  for (int i=0; i<31; i++) _layout -> setRowStretch(i, 1);

  for (int i=0; i<151; ++i) {
    const PkmnSpecies *actualPkmn = PkmnSpeciesList::getByIndex(i+1);
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
  PkmnElementPickerView *elementMenu = new PkmnElementPickerView(this);
  connect (elementMenu, SIGNAL(elementSelected(int)),
           this,        SLOT(selectByElement(int)));
  elementSelect->setMenu(elementMenu);

  QVBoxLayout *vlayout = new QVBoxLayout(this);
  vlayout -> addWidget(elementSelect);
  vlayout -> addWidget(scrollArea);
  //vlayout -> addStretch(1);

  setLayout(vlayout);
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
    std::vector<const PkmnSpecies *> list = PkmnSpeciesList::getByElement(element);
    for (unsigned int i=0; i<list.size(); i++) {
      _layout -> addWidget(_pkmns[list[i]->getIndex()-1], i/5, i%5);
      //_pkmns[i] -> setGeometry(QRect(5+100*(i%5), 5+90*(i/5), 95, 85));
      _pkmns[list[i]->getIndex()-1] -> setVisible(true);
    }
  }
}
