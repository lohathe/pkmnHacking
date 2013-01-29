#ifndef PKMN_PARTY_VIEW
#define PKMN_PARTY_VIEW

#include <string>
using std::string;

#include <QWidget>

class PkmnSaveStateModel;

class PkmnPartyView : public QWidget {

  Q_OBJECT

public:

  PkmnPartyView(QWidget *, PkmnSaveStateModel *);

  void updateSelectedPartyPkmn(int);
  void displayPkmnInfo(int);
  void displaySpeciesPicker();
  void displayMovePicker();

signals:

  void partyPkmnSelectedEvent(int);

  void createPkmnEvent();
  void deletePkmnEvent();

  void pkmnSpeciesSelectedEvent(int);
  void pkmnNameChangedEvent(const string &);
  void pkmnParameterChangedEvent(int, int);

  void saveToFileEvent();

private:

};

#endif // PKMN_PARTY_VIEW
