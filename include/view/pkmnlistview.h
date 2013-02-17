#ifndef PKMN_LIST_VIEW
#define PKMN_LIST_VIEW

#include <QWidget>

#include <vector>
using std::vector;

#include "pkmnlistitemview.h"
#include "pkmnspecies.h"

class PkmnPartyListView : public QWidget {

  Q_OBJECT

public:

  PkmnPartyListView (QWidget *);

  void setSelectedPartyPkmn (int);
  void updateWholeList (vector<const PkmnSpecies *>);
  void updateSingleItem (const PkmnSpecies *, int);

public slots:

signals:

  void selectPkmnEvent (int);

private:

  PkmnSpeciesListItem *_activePkmnList[6];

};

#endif // PKMN_LIST_VIEW
