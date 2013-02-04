#ifndef PKMN_PARTY_LIST_VIEW
#define PKMN_PARTY_LIST_VIEW

#include <QWidget>

#include <vector>
using std::vector;

#include "pkmnpartylistitemview.h"
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

  PkmnPartyListItem *_activePkmnList[6];

};

#endif // PKMN_PARTY_LIST_VIEW
