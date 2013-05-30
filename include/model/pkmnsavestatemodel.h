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

  bool saveToFile() const;
  bool openFile(const string &);

  // GENERAL INFO
  int getTrainerId() const;

  // PARTY PKMN INFO
  vector<const PkmnSpecies *> getPartyPkmnList() const;
  int getPartyPkmnCount() const;

  int  getPartyPkmnParameter(int, int);
  string getPartyPkmnName(int);
  PkmnState getPartyPkmnInfo(int) const;
  bool setPartyPkmnParameter(int, int, int);
  bool setPartyPkmnStrParam(int, int, const string &);
  
  bool createPartyPkmnAtIndex(int, int);
  bool deletePartyPkmnAtIndex(int);

  // BOX PKMN INFO
  vector<const PkmnSpecies *> getBoxPkmnList(int) const;
  int getBoxPkmnCount(int) const;

  int getBoxPkmnParam(int, int, int) const;
  string getBoxPkmnStrParam(int, int, int) const;
  bool setBoxPkmnParam(int, int, int, int);
  bool setBoxPkmnStrParam(int, int, int, string);
  PkmnState getBoxPkmnState(int, int) const;

  bool createBoxPkmnAtIndex(int, int, int);
  bool deleteBoxPkmnAtIndex(int, int);
  
  // POKEDEX PKMN INFO
  PkmnPokedex getPkmnPokedex() const;
  bool setPkmnPokedexSeen(int, bool);
  bool setPkmnPokedexCatched(int, bool);

signals:

  void changedPkmnPartyListEvent();
  void changedPkmnPartyInfoEvent();

  void changedPkmnBoxListEvent();
  void chengedPkmnBoxInfoEvent();

  void changedPkmnPokedexEvent();

public slots:


private:

  PkmnSaveState* _saveState;


};

#endif // PKMN_SAVE_STATE_MODEL
