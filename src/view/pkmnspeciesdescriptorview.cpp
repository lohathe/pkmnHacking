#include "pkmnspeciesdescriptorview.h"

#include "pkmnspeciesdescriptor.h"
#include "pkmnspecies.h"
#include "pkmnmove.h"

#include <QPainter>
#include <QString>
#include <QLabel>

PkmnSpeciesDescriptorView::PkmnSpeciesDescriptorView (QWidget *parent)
  : QWidget(parent), _displayedPkmnIndex(0) { }

void PkmnSpeciesDescriptorView::displayDescriptionFor(int index) {

  if (index == _displayedPkmnIndex)
    return;

  _displayedPkmnIndex = index;
  update();

}

void PkmnSpeciesDescriptorView::paintEvent(QPaintEvent *) {

  QPainter p(this);

  //if (_displayedPkmnIndex)
    p.fillRect(0, 0, 200, 300, Qt::red);

  PkmnSpeciesDescriptor *description =
      PkmnSpeciesDescriptorList::get(_displayedPkmnIndex);
  p.drawText(10, 10,QString::fromStdString(PkmnSpeciesList::getByIndex(description->getIndex())->getUpperCaseName()));


}

