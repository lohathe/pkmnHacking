#include "pkmnlistitemview.h"

#include <QFontMetrics>
#include <QPainter>
#include <QString>

// PKMN SPECIES LIST ITEM

PkmnSpeciesListItem::PkmnSpeciesListItem(QWidget *parent, int index) :
  QWidget(parent), _itemIndex(index), _isSelected(false), _isMouseOver(false) {

  this -> setFixedSize(200, 60);

}

void PkmnSpeciesListItem::updateItem(const PkmnSpecies *pkmnInfo) {

  if (pkmnInfo->getId() == _pkmnInfo.getId())
    return;
  _pkmnInfo = *(const_cast<PkmnSpecies *>(pkmnInfo));
  setEnabled(_pkmnInfo.isValid());
  update();
}

void PkmnSpeciesListItem::setSelected(bool selected) {

  _isSelected = selected;

  update();

}

void PkmnSpeciesListItem::mousePressEvent (QMouseEvent *) {
  emit pkmnSelected(_itemIndex);
}
void PkmnSpeciesListItem::enterEvent (QEvent *) {
  if (_isMouseOver)
    return;
  _isMouseOver = true;
  update();
}
void PkmnSpeciesListItem::leaveEvent (QEvent *) {
  if (!_isMouseOver)
    return;
  _isMouseOver = false;
  update();
}

void PkmnSpeciesListItem::paintEvent ( QPaintEvent *) {

  QPainter p (this);

  if (_isMouseOver && !_isSelected) {
    p.fillRect(0, 10, 200, 40, QColor(200,200,160));
  }
  if (_isSelected) {
    p.fillRect(0, 10, 200, 40, QColor(255, 255, 200));
  }

  int imgOffset = 10, textOffset = 80;
  if (_itemIndex % 2 == 0) {
    imgOffset = 130;
    textOffset = 120 - p.fontMetrics().width(QString::fromStdString(_pkmnInfo.getName()));
  }
  if (_pkmnInfo.isValid()) {
    p.drawPixmap (imgOffset, 2,
                  QPixmap(":/img/spritesyellowcolor.png")
                    .copy(1+57*((_pkmnInfo.getIndex()-1)%12),
                          1+57*((_pkmnInfo.getIndex()-1)/12),
                          56, 56));
    p.drawText(textOffset, 38, QString::fromStdString(_pkmnInfo.getName()));
  } else {
    p.drawPixmap (imgOffset, 2, QPixmap(":/img/pokeballSprite.png"));
    p.drawText(textOffset, 38, "empty slot");
  }

}

// PKMN MOVE LIST ITEM

PkmnMoveListItem::PkmnMoveListItem (QWidget *parent, int index)
  : QWidget(parent), _moveIndex(index-1), _pkmnMove(*PkmnMoveList::get(index)),
     _isSelected(false), _isMouseOver(false) {

  setFixedSize(500, 25);


}

void PkmnMoveListItem::setIndex(int value) {
  _moveIndex = value;
  update();
}

void PkmnMoveListItem::mousePressEvent (QMouseEvent *) {
  emit moveSelected(_pkmnMove.getId());
}
void PkmnMoveListItem::enterEvent (QEvent *) {
  if (_isMouseOver)
    return;
  _isMouseOver = true;
  update();
}
void PkmnMoveListItem::leaveEvent (QEvent *) {
  if (!_isMouseOver)
    return;
  _isMouseOver = false;
  update();
}

void PkmnMoveListItem::paintEvent (QPaintEvent *) {

  QPainter p (this);

  if (_isMouseOver) {
    p.fillRect(0, 0, width(), height(), QColor(255, 255, 200));
  } else if (_moveIndex % 2 == 0) {
    p.fillRect(0, 0, width(), height(), QColor(200, 200, 200));
  }

  p.drawText(5,   20, QString::number(_pkmnMove.getId()) + " " + QString::fromStdString(_pkmnMove.getName()));
  p.drawText(285, 20, "(" + QString::fromStdString(Element::toString(_pkmnMove.getElement())) + ")");
  p.drawText(405, 20, QString::number(_pkmnMove.getPwr()));
  p.drawText(455, 20, QString::number(_pkmnMove.getPP()));

}
