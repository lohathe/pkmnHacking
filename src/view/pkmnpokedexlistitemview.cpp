#include "pkmnpokedexlistitemview.h"

#include <QPainter>
#include <QPaintEvent>
#include <QEvent>
#include <QFormLayout>
#include <QHBoxLayout>

/*
 INSERT MODEL TO CHECK ENUM!!!!
 0x01 == PKMN SEEN
 0x02 == PKMN CATCHED
*/
int PKMN_SEEN    = 0x01;
int PKMN_CATCHED = 0x02;

PkmnPokedexListItemView::PkmnPokedexListItemView(int pkmnIndex, QWidget *parent) :
  QWidget(parent),
  _pkmnInfo(PkmnSpeciesList::getBy(PkmnSpeciesList::INDEX, pkmnIndex)[0]),
  _pkmnPokedexStatus(3), _isMouseOver(false) {

  setFixedSize(300, 60);

  _pkmnSeen = new QCheckBox(this);
  //_pkmnSeen -> setLayoutDirection(Qt::RightToLeft);
  _pkmnCatched = new QCheckBox(this);
  //_pkmnCatched -> setLayoutDirection(Qt::RightToLeft);
  QFormLayout *form = new QFormLayout();
  form -> setLabelAlignment(Qt::AlignRight);
  form -> addRow("seen", _pkmnSeen);
  form -> addRow("catched", _pkmnCatched);
  QHBoxLayout *layout = new QHBoxLayout();
  layout -> addStretch(1);
  layout -> addLayout(form);
  setLayout(layout);

  connect (_pkmnSeen, SIGNAL(clicked()), this, SLOT(manageButtonClicked()));
  connect (_pkmnCatched, SIGNAL(clicked()), this, SLOT(manageButtonClicked()));

}

void PkmnPokedexListItemView::updateItem(int pokedexStatus) {

  if (pokedexStatus == _pkmnPokedexStatus)
    return;

  _pkmnPokedexStatus = pokedexStatus;
  _pkmnSeen    -> setChecked(_pkmnPokedexStatus & PKMN_SEEN);
  _pkmnCatched -> setChecked(_pkmnPokedexStatus & PKMN_CATCHED);

  update();

}

void PkmnPokedexListItemView::paintEvent(QPaintEvent *e) {

  QPainter p (this);

  if (_isMouseOver) {
    p.fillRect(0, 10, 300, 40, QColor(255, 255,200));
  }
  if (_pkmnInfo->getIndex()%2 == 1) {
    p.fillRect(0, 10, 300, 40, QColor(200, 200, 160));
  }

  if (_pkmnPokedexStatus & PKMN_SEEN) {
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

  if (_pkmnPokedexStatus & PKMN_CATCHED) {
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

void PkmnPokedexListItemView::manageButtonClicked() {

  int pokedexStatus = 0;
  if (_pkmnSeen -> isChecked())
    pokedexStatus = pokedexStatus | PKMN_SEEN;
  if (_pkmnCatched -> isChecked())
    pokedexStatus = pokedexStatus | PKMN_CATCHED;

  emit pkmnPokedexStatusChangedEvent(_pkmnInfo->getId(), pokedexStatus);

}
