#ifndef PKMN_LIST_ITEM_VIEW
#define PKMN_LIST_ITEM_VIEW

#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QWidget>

#include <string>
using std::string;

#include "pkmnspecies.h"
#include "pkmnmove.h"

class PkmnSpeciesListItem : public QWidget {

  Q_OBJECT

public:

  PkmnSpeciesListItem(QWidget *,int);

  void updateItem(const PkmnSpecies*);
  void setSelected(bool);

signals:

  void pkmnSelected(int);

protected:

  virtual void paintEvent (QPaintEvent *) = 0;
  virtual void mousePressEvent (QMouseEvent *);
  virtual void enterEvent (QEvent *);
  virtual void leaveEvent (QEvent *);

//private:

  int         _itemIndex;
  PkmnSpecies _pkmnInfo;

  bool   _isSelected;
  bool   _isMouseOver;

};

class PkmnSpeciesListItemLarge : public PkmnSpeciesListItem {

  Q_OBJECT

public:
  PkmnSpeciesListItemLarge(QWidget *,int);

protected:
  virtual void paintEvent (QPaintEvent *);

};

class PkmnSpeciesListItemSmall : public PkmnSpeciesListItem {

  Q_OBJECT

public:
  PkmnSpeciesListItemSmall(QWidget *,int);

protected:
  virtual void paintEvent (QPaintEvent *);

};

class PkmnMoveListItem : public QWidget {

  Q_OBJECT

public:

  PkmnMoveListItem(QWidget *, int);

  void setIndex(int);

signals:

  void moveSelected(int);

protected:

  virtual void paintEvent (QPaintEvent *);
  virtual void mousePressEvent (QMouseEvent *);
  virtual void enterEvent (QEvent *);
  virtual void leaveEvent (QEvent *);

private:

  int      _moveIndex;
  PkmnMove _pkmnMove;

  bool _isSelected;
  bool _isMouseOver;

};

#endif // PKMN_LIST_ITEM_VIEW
