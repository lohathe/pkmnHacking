#ifndef PKMN_POKEDEX_LIST_ITEM_VIEW
#define PKMN_POKEDEX_LIST_ITEM_VIEW

#include <QWidget>
#include <QCheckBox>

#include "pkmnspecies.h"

class PkmnPokedexListItemView : public QWidget {

  Q_OBJECT

public:

  PkmnPokedexListItemView(int, QWidget *);

  void updateItem(int);

signals:

  void pkmnPokedexStatusChangedEvent(int, int);

public slots:

  virtual void paintEvent (QPaintEvent *);
  virtual void enterEvent (QEvent *);
  virtual void leaveEvent (QEvent *);

private slots:

  void manageButtonClicked();

private:

  const PkmnSpecies *_pkmnInfo;
  int _pkmnPokedexStatus;

  bool _isMouseOver;
  QCheckBox *_pkmnSeen;
  QCheckBox *_pkmnCatched;

};

#endif // PKMN_POKEDEX_LIST_ITEM_VIEW
