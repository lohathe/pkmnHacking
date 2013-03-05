#ifndef PKMN_BOX_CONTROLLER
#define PKMN_BOX_CONTROLLER

#include <QObject>

#include <string>
using std::string;

class PkmnSaveStateModel;
class PkmnBoxView;

class PkmnBoxController : public QObject {

  Q_OBJECT

public:

  PkmnBoxController(PkmnSaveStateModel *, PkmnBoxView *);

signals:

  void operationOutcome (bool, const string &);

public slots:

  // SYNCHRONIZE THE VIEWS
  void manageBoxSelected(int);
  void manageBoxPkmnSelected(int);

  // MODIFY THE MODEL
  void manageCreatePkmn();
  void manageDeletePkmn();
  void manageDeleteBox();
  void manageSpeciesChange();
  void manageMoveChange(int);

  void managePkmnSpeciesSelected(int);
  void managePkmnMoveSelected(int);
  void managePkmnStrParamChanged(int, const string &);
  void managePkmnParameterChanged(int, int);

private:

  PkmnSaveStateModel *_model;
  PkmnBoxView *_view;

  int _selectedBoxIndex;
  int _selectedPkmnIndex;
  int _selectedMoveIndex;
  bool _isCreatingPkmn;
  bool _isChangingMove;

};

#endif // PKMN_BOX_CONTROLLER

