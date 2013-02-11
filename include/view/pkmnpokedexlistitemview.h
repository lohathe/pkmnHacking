#ifndef PKMN_POKEDEX_LIST_ITEM_VIEW
#define PKMN_POKEDEX_LIST_ITEM_VIEW

#include <QWidget>

#include "pkmnspecies.h"

class PkmnPokedexListItemView : public QWidget {

  Q_OBJECT

public:

  PkmnPokedexListItemView(int, QWidget *);

  void updateItem(bool, bool);

signals:

  void clickedEvent(int);
  void displayInfoEvent(int);

public slots:

protected:

  virtual void paintEvent (QPaintEvent *);
  virtual void enterEvent (QEvent *);
  virtual void leaveEvent (QEvent *);
  virtual void mousePressEvent(QMouseEvent *);

private slots:

private:

  const PkmnSpecies *_pkmnInfo;
  bool _isSeen;
  bool _isCatched;

  bool _isMouseOver;

};

#endif // PKMN_POKEDEX_LIST_ITEM_VIEW
