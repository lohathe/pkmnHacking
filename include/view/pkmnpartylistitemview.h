#ifndef PKMN_PARTY_LIST_ITEM_VIEW
#define PKMN_PARTY_LIST_ITEM_VIEW

#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QWidget>

#include <string>
using std::string;

#include "pkmnspecies.h"

class PkmnPartyListItem : public QWidget {

  Q_OBJECT

public:

  PkmnPartyListItem(QWidget *,int);

  void updateItem(const PkmnSpecies*);
  void setSelected(bool);

signals:

  void pkmnSelected(int);

protected:

  virtual void paintEvent (QPaintEvent *);
  virtual void mousePressEvent (QMouseEvent *);
  virtual void enterEvent (QEvent *);
  virtual void leaveEvent (QEvent *);

private:

  int         _itemIndex;
  PkmnSpecies _pkmnInfo;
  string      _pkmnNick;

  bool   _isSelected;
  bool   _isMouseOver;

};

#endif // PKMN_PARTY_LIST_ITEM_VIEW
