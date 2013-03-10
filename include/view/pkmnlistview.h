#ifndef PKMN_LIST_VIEW
#define PKMN_LIST_VIEW

#include <QWidget>

#include <vector>
using std::vector;

#include "pkmnlistitemview.h"
#include "pkmnspecies.h"

class PkmnListView : public QWidget {

  Q_OBJECT

public:

  void setSelectedPartyPkmn (int);
  void updateWholeList (vector<const PkmnSpecies *>);
  void updateSingleItem (const PkmnSpecies *, int);

public slots:

signals:

  void selectPkmnEvent (int);

protected:

  PkmnListView (QWidget *);
  virtual void initialize(int, int);

  vector<PkmnSpeciesListItem *> _activePkmnList;

};

class PkmnListViewSmallIcon: public PkmnListView {

  Q_OBJECT

public:
  PkmnListViewSmallIcon(QWidget *, int, int, int);

};

class PkmnListViewLargeIcon: public PkmnListView {

  Q_OBJECT

public:
  PkmnListViewLargeIcon(QWidget *, int, int, int);

};

#endif // PKMN_LIST_VIEW
