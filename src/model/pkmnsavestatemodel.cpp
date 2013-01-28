#ifndef PKMN_SAVE_STATE_MODEL
#define PKMN_SAVE_STATE_MODEL

#include <QObject>

#include <vector>
using std::vector;

#include "pkmnsavestate.h"
#include "pkmnstate.h"
#include "pkmnspecies.h"

class PkmnSaveStateModel : public QObject {

  Q_OBJECT;

private:

  PkmnSaveState* _saveState;

public:

  PkmnSaveStateModel (PkmnSaveState*);

  vector<const PkmnSpecies *> getPkmnList() const;
  PkmnState* getPkmnInfo(int) const;
  int getPkmnListNumber() const;
  int getTrainerId() const;
  
  void setPkmnState(PkmnState*);
  
  bool createPkmnAtIndex(int);
  bool deletePkmnAtIndex(int);
  
  void saveToFile() const;

signals:

  //void changedPkmnList(int, Pkmn*);
  void changedPkmnListEvent();
  void changedPkmnInfoEvent();

public slots:

};

#endif // PKMN_SAVE_STATE_MODEL
