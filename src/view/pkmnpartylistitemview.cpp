#include "pkmnpartylistitemview.h"

#include <QFontMetrics>
#include <QPainter>
#include <QString>

PkmnPartyListItem::PkmnPartyListItem(QWidget *parent, int index) :
  QWidget(parent), _itemIndex(index), _isSelected(false), _isMouseOver(false) {

  this -> setFixedSize(200, 60);

}

void PkmnPartyListItem::updateItem(const PkmnSpecies *pkmnInfo) {

  if (pkmnInfo->getId() == _pkmnInfo.getId())
    return;
  _pkmnInfo = *(const_cast<PkmnSpecies *>(pkmnInfo));
  setEnabled(_pkmnInfo.isValid());
  update();
}

void PkmnPartyListItem::setSelected(bool selected) {

  _isSelected = selected;

  update();

}

void PkmnPartyListItem::mousePressEvent (QMouseEvent *) {
  emit pkmnSelected(_itemIndex);
}
void PkmnPartyListItem::enterEvent (QEvent *) {
  if (_isMouseOver)
    return;
  _isMouseOver = true;
  update();
}
void PkmnPartyListItem::leaveEvent (QEvent *) {
  if (!_isMouseOver)
    return;
  _isMouseOver = false;
  update();
}

void PkmnPartyListItem::paintEvent ( QPaintEvent *) {

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
