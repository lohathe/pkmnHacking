#ifndef PKMN_POKEDEX_VIEW
#define PKMN_POKEDEX_VIEW

#include <QWidget>

class PkmnSaveStateModel;

class PkmnPokedexView : public QWidget {

  Q_OBJECT

public:
  PkmnPokedexView (QWidget *);

  void connectModel(PkmnSaveStateModel *);

signals:

  void pkmnPokedexEntryChanged(int, int);

public slots:

private:

  PkmnSaveStateModel *_model;

};

#endif // PKMN_POKEDEX_VIEW
