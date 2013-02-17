#ifndef PKMN_PARTY_CONTROLLER
#define PKMN_PARTY_CONTROLLER

#include <string>
using std::string;

#include <QObject>
#include <QAction>

class PkmnSpeciesDescriptor;
class PkmnSaveStateModel;
class PkmnPartyView;

class PkmnPartyController : public QObject {

  Q_OBJECT

public:

  PkmnPartyController (PkmnSaveStateModel *, PkmnPartyView *);

signals:

  void operationOutcomeEvent (bool, const string &);

public slots:

  void manageEnableCoherency(bool);

  // SYNCHRONIZE THE VIEWS
  void managePartyPkmnSelected(int);

  // MODIFY THE MODEL
  void manageCreatePkmn();
  void manageDeletePkmn();
  void manageSpeciesChange();
  void manageMoveChange(int);

  void managePkmnSpeciesSelected(int);
  void managePkmnMoveSelected(int);
  void managePkmnStrParamChanged(int, const string &);
  void managePkmnParameterChanged(int, int);

private slots:

private:

  int _selectedPartyIndex;
  int _selectedMoveIndex;

  bool _isCreatingPkmn;
  bool _isChangingMove;

  bool _coherencyEnabled;

  PkmnSaveStateModel *_model;
  PkmnPartyView *_view;

  // UTILITY METHODS

  const PkmnSpeciesDescriptor *getSelectedPkmnSpeciesDescriptor() const;

  void manageIVParameter(int, int);
  void manageHPParameter(int, int);
  void manageLvlParameter(int, int);
  void manageSpeciesParameter(int, int);
  void manageAlimentParameter(int, int);
  void managePPParameter(int, int);
  void setPartyPkmnBasicStats(int);

};

#endif // PKMN_PARTY_CONTROLLER
