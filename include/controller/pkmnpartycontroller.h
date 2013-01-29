#ifndef PKMN_PARTY_CONTROLLER
#define PKMN_PARTY_CONTROLLER

#include <string>
using std::string;

#include <QObject>

class PkmnSaveStateModel;
class PkmnPartyView;

class PkmnPartyController : public QObject {

  Q_OBJECT

public:

  PkmnPartyController (PkmnSaveStateModel *, PkmnPartyView *);

signals:

  void operationOutcomeEvent (bool, const string &);

public slots:

  // SYNCHRONIZE THE VIEWS
  void managePartyPkmnSelected(int);

  // MODIFY THE MODEL
  void manageCreatePkmn();
  void manageDeletePkmn();
  void manageMoveChange(int);

  void managePkmnSpeciesSelected(int);
  void managePkmnMoveSelected(int);
  void managePkmnNameChanged(const string &);
  void managePkmnParameterChanged(int, int);

  void manageSaveToFile();

private slots:

  void manageOperationOutcome(bool, const string &);

private:

  int _selectedPartyIndex;
  bool _isCreatingPkmn;

  bool _isChangingMove;
  int _selectedMoveIndex;

  PkmnSaveStateModel *_model;
  PkmnPartyView *_view;

  // UTILITY METHODS

  void manageIVParameter(int, int);
  void manageHPParameter(int, int);
  void manageLvlParameter(int, int);
  void manageSpeciesParameter(int, int);
  void manageAlimentParameter(int, int);
  void managePPParameter(int, int);

};

#endif // PKMN_PARTY_CONTROLLER
