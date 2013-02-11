#include "pkmnspeciesdescriptorview.h"

#include "pkmnspeciesdescriptor.h"
#include "pkmnspecies.h"
#include "pkmnmove.h"

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QString>

PkmnSpeciesDescriptorView::PkmnSpeciesDescriptorView (QWidget *parent)
  : QWidget(parent), _displayedPkmnIndex(0) {
  setMinimumSize(300, 200);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void PkmnSpeciesDescriptorView::displayDescriptionFor(int index) {

  if (index == _displayedPkmnIndex)
    return;

  _displayedPkmnIndex = index;
  update();

}

void PkmnSpeciesDescriptorView::mouseReleaseEvent(QMouseEvent *e) {

  int x = e->x();
  int y = e->y();
  for (unsigned int i=0; i<_mouseLinks.size(); ++i) {
    Link l = _mouseLinks[i];
    if (x > l._x && x < (l._x + l._dim))
      if (y > l._y && y < (l._y + l._dim)) {
        // emit CLICK!!!!!
        _displayedPkmnIndex = l._info;
        update();
        return;
      }
  }

}

void PkmnSpeciesDescriptorView::paintEvent(QPaintEvent *) {

  if (_displayedPkmnIndex < 1 || _displayedPkmnIndex > 151)
    return;

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing, true);

  QFont fontBold("SansSerif", 12, QFont::Bold);
  QFont fontNormal("SansSerif", 12, QFont::Normal);
  QFont fontTitle("SansSerif", 22, 52);
  QFont fontSmall("SansSerif", 10);
  QBrush darkGray(QColor(100, 100, 100));

  int w = width();
  int h = height();

  const PkmnSpeciesDescriptor *description =
      PkmnSpeciesDescriptorList::get(_displayedPkmnIndex);
  const PkmnSpecies *species =
      PkmnSpeciesList::getByIndex(_displayedPkmnIndex);
  const vector<MoveLevel> moves =
      description -> getLearningSet();
  const vector<int> prevEvolutions = description -> getPrevEvolutions();
  const vector<int> nextEvolutions = description -> getNextEvolutions();

  // Draw background and image of pokemon
  p.setBrush( darkGray );

  p.drawRoundedRect(0, 0, w-2, 75, 20, 20);
  p.setBrush( Qt::NoBrush );

  // Draw all evolutions
  int evdim = 56;
  int evx = w - 5 - evdim*2 - prevEvolutions.size()*evdim - nextEvolutions.size()*evdim;
  int evy = 60;
  int count = 0;
  p.setPen(Qt::black);
  p.setFont(fontSmall);
  _mouseLinks.clear();
  for (int i=prevEvolutions.size()-1; i>=0; --i) {
    _mouseLinks.push_back(Link(evx + count*evdim, evy, evdim, prevEvolutions[i]));
    p.drawPixmap(evx + count*evdim, evy,
                 QPixmap(":/img/spritesyellowgray.png")
                   .copy(1+57*((prevEvolutions[i]-1)%12),
                         1+57*((prevEvolutions[i]-1)/12),
                         56, 56));
    QString evmethod =
        QString::fromStdString(PkmnSpeciesDescriptorList::
                               get(prevEvolutions[i])->getEvMethodString());
    p.drawText(evx + count*evdim + (evdim - fontMetrics().width(evmethod))/2,
               evy + evdim + 2 + fontSmall.pointSize(), evmethod);
    count++;
  }
  p.drawPixmap(evx + count*evdim, evy - evdim,
               QPixmap(":/img/spritesyellowcolor.png")
                 .copy(1+57*((species->getIndex()-1)%12),
                       1+57*((species->getIndex()-1)/12),
                       56, 56).scaled(2*evdim, 2*evdim));
  QString evmethod = QString::fromStdString(description->getEvMethodString());
  p.drawText(evx + count*evdim + (2*evdim - fontMetrics().width(evmethod))/2,
             evy + evdim + 2 + fontSmall.pointSize(), evmethod);
  count = count + 2; // becasue dim value is double in respect to other pictures
  for (unsigned int i=0; i<nextEvolutions.size(); ++i) {
    _mouseLinks.push_back(Link(evx + count*evdim, evy, evdim, nextEvolutions[i]));
    p.drawPixmap(evx + count*evdim, evy,
                 QPixmap(":/img/spritesyellowgray.png")
                   .copy(1+57*((nextEvolutions[i]-1)%12),
                         1+57*((nextEvolutions[i]-1)/12),
                         56, 56));
    QString evmethod =
        QString::fromStdString(PkmnSpeciesDescriptorList::
                               get(nextEvolutions[i])->getEvMethodString());
    p.drawText(evx + count*evdim + (evdim - fontMetrics().width(evmethod))/2,
               evy + evdim + 2 + fontSmall.pointSize(), evmethod);
    count++;
  }

  // Draw name and type of pokemon
  QPainterPath title;
  title.addText(10, 10+fontTitle.pointSize(), fontTitle, QString::fromStdString(species->getUpperCaseName()));
  p.setBrush(QBrush(Qt::white));
  p.drawPath(title);
  p.setBrush(Qt::NoBrush);

  QString element = "( " +
      QString::fromStdString(Element::toUpperString(species->getElement1()));
  if (species->getElement2() != species->getElement1())
    element += "/" + QString::fromStdString(Element::toUpperString(species->getElement2()));
  element += " )";
  p.setPen(Qt::white);
  p.setFont(fontNormal);
  p.drawText(10, 16 + fontTitle.pointSize() + fontNormal.pointSize(), element);
  p.setPen(Qt::black);

  // Draw learnset
  int moveRowHeight = 24,  moveRowWidth = w - 40;
  int moveRowYStart = h - moves.size()*moveRowHeight - 10, moveRowXStart = 20;
  QFontMetrics fmetric(fontBold);
  int moveNameX = moveRowXStart + fmetric.width("XXXXX") + 15;
  int moveElementX = moveNameX + fmetric.width("XXXXXXXXXXXXX") + 5;
  p.setFont(fontNormal);

  bool wasStarting = true;
  for (unsigned int i=0; i<moves.size(); ++i) {
    if (i % 2 == 0)
      p.fillRect(moveRowXStart, moveRowYStart + moveRowHeight*i, moveRowWidth, moveRowHeight, QColor(200,200,200));
    const PkmnMove *move = PkmnMoveList::get(moves[i].getMove());
    if (moves[i].getLevel() == 0)
      p.drawText(25, moveRowYStart + moveRowHeight*(i+1) - 5, "Start");
    else
      p.drawText(25, moveRowYStart + moveRowHeight*(i+1) - 5, QString::number(moves[i].getLevel()));

    if (move->getType() != Type::STATUS &&
        (move->getElement() == species->getElement1() ||
         move->getElement() == species->getElement2())) {
      p.setFont(fontBold);
    }
    p.drawText(moveNameX, moveRowYStart + moveRowHeight*(i+1) - 5, QString::fromStdString(move->getName()));
    p.drawText(moveElementX, moveRowYStart + moveRowHeight*(i+1) - 5, QString::fromStdString("["+Element::toUpperString(move->getElement()))+"]");
    if (move->getType() != Type::STATUS &&
        (move->getElement() == species->getElement1() ||
         move->getElement() == species->getElement2())) {
      p.setFont(fontNormal);
    }
    if (wasStarting && moves[i].getLevel() != 0) {
      wasStarting = false;
      p.drawLine(moveRowXStart, moveRowYStart + moveRowHeight*i,
                 moveRowXStart+moveRowWidth, moveRowYStart + moveRowHeight*i);
    }

  }
  p.drawRect(moveRowXStart, moveRowYStart, moveRowWidth, moveRowHeight*moves.size());

}

