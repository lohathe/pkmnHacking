#include "pkmnpokedexlistitemview.h"

#include <QPainter>
#include <QPaintEvent>
#include <QEvent>
#include <QFormLayout>
#include <QHBoxLayout>

PkmnPokedexListItemView::PkmnPokedexListItemView(int pkmnIndex, QWidget *parent) :
  QWidget(parent),
  _pkmnInfo(PkmnSpeciesList::getBy(PkmnSpeciesList::INDEX, pkmnIndex)[0]),
  _isSeen(false), _isCatched(false), _isMouseOver(false) {

  setFixedSize(300, 60);

}

void PkmnPokedexListItemView::updateItem(bool isSeen, bool isCatched) {

  if (isSeen == _isSeen && isCatched == _isCatched)
    return;

  _isSeen = isSeen;
  _isCatched = isCatched;

  update();

}

void PkmnPokedexListItemView::paintEvent(QPaintEvent *e) {

  QPainter p (this);

  if (_isMouseOver) {
    p.fillRect(0, 10, 300, 40, QColor(255, 255,200));
  }
  if (_pkmnInfo->getIndex()%2 == 1 && !_isMouseOver) {
    p.fillRect(0, 10, 300, 40, QColor(200, 200, 160));
  }

  if (_isSeen) {
    p.drawPixmap (10, 2,
                  QPixmap(":/img/spritesyellowcolor.png")
                    .copy(1+57*((_pkmnInfo->getIndex()-1)%12),
                          1+57*((_pkmnInfo->getIndex()-1)/12),
                          56, 56));
  } else {
    p.drawPixmap(10, 2,
                 QPixmap(":/img/spritesyellowgray.png")
                   .copy(1+57*((_pkmnInfo->getIndex()-1)%12),
                         1+57*((_pkmnInfo->getIndex()-1)/12),
                         56, 56));
  }

  if (_isCatched) {
    p.drawPixmap (5, 28, QPixmap(":/img/pokeballSprite.png").scaled(30,30));
  }
  p.drawText(80, 38, QString::fromStdString(_pkmnInfo->getName()));

  QWidget::paintEvent(e);

}

void PkmnPokedexListItemView::enterEvent(QEvent *) {
  if (_isMouseOver)
    return;
  _isMouseOver = true;
  update();
}

void PkmnPokedexListItemView::leaveEvent(QEvent *) {
  if (!_isMouseOver)
    return;
  _isMouseOver = false;
  update();
}

void PkmnPokedexListItemView::mousePressEvent(QMouseEvent *) {

  emit clickedEvent(_pkmnInfo->getIndex());
}

/*
void PkmnPokedexListItemView::manageButtonClicked() {

  int pokedexStatus = 0;
  if (_pkmnSeen -> isChecked())
    pokedexStatus = pokedexStatus | PKMN_SEEN;
  if (_pkmnCatched -> isChecked())
    pokedexStatus = pokedexStatus | PKMN_CATCHED;

  emit pkmnPokedexStatusChangedEvent(_pkmnInfo->getIndex(), pokedexStatus);

}*/
