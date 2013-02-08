#ifndef PKMN_POKEDEX_VIEW
#define PKMN_POKEDEX_VIEW

#include <QWidget>

#include "pkmnpokedexlistitemview.h"

class PkmnSaveStateModel;

class PkmnPokedexView : public QWidget {

  Q_OBJECT

public:
  PkmnPokedexView (QWidget *);

  void connectModel(PkmnSaveStateModel *);

signals:

  void pkmnPokedexEntryClicked(int);

public slots:

  void updateList();

private:

  PkmnSaveStateModel *_model;
  PkmnPokedexListItemView *_pkmnList[151];

};

#endif // PKMN_POKEDEX_VIEW
