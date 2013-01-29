#ifndef PKMN_SAVE_STATE_MODEL
#define PKMN_SAVE_STATE_MODEL

#include <QObject>

#include <string>
using std::string;
#include <vector>
using std::vector;

#include "pkmnsavestate.h"
#include "pkmnstate.h"
#include "pkmnspecies.h"

class PkmnSaveStateModel : public QObject {

  Q_OBJECT

public:

  PkmnSaveStateModel (PkmnSaveState*);

  int getTrainerId() const;

  vector<const PkmnSpecies *> getPartyPkmnList() const;
  int getPartyPkmnCount() const;

  int  getPartyPkmnParameter(int, int);
  string getPartyPkmnName(int);
  PkmnState* getPartyPkmnInfo(int) const;
  bool setPartyPkmnParameter(int, int, int);
  bool setPartyPkmnName(int, string);
  
  bool createPartyPkmnAtIndex(int, int);
  bool deletePartyPkmnAtIndex(int);
  
  bool saveToFile() const;

signals:

  void changedPkmnPartyListEvent();
  void changedPkmnPartyInfoEvent();

public slots:


private:

  PkmnSaveState* _saveState;


};

#endif // PKMN_SAVE_STATE_MODEL
