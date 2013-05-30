#ifndef PKMN_PARTY_CONTROLLER
#define PKMN_PARTY_CONTROLLER

#include <string>
using std::string;

#include <QObject>
#include <QAction>

#include "pkmnparametercontroller.h"

class PkmnSpeciesDescriptor;
class PkmnSaveStateModel;
class PkmnPartyView;

class PkmnPartyController : public PkmnParameterController {

  Q_OBJECT

public:

  PkmnPartyController (PkmnSaveStateModel *, PkmnPartyView *);

public slots:

  virtual void manageEnableCoherency(bool);

  // SYNCHRONIZE THE VIEWS
  void managePartyPkmnSelected(int);

  // MODIFY THE MODEL
  void manageCreatePkmn();
  void manageDeletePkmn();
  void manageSpeciesChange();
  void manageMoveChange(int);

  void managePkmnSpeciesSelected(int);
  void managePkmnMoveSelected(int);
  //virtual void managePkmnStrParamChanged(int, const string &);
  //virtual void managePkmnParamChanged(int, int);

private slots:

protected:

  virtual const PkmnSpeciesDescriptor *getCurrentPkmnSpeciesDescriptor() const;

  virtual bool isCurrentPkmnValid() const;

  virtual const PkmnState getCurrentPkmnInfo() const;

  virtual int getCurrentPkmnParam(int) const;
  virtual void setCurrentPkmnParam(int, int);

  virtual string getCurrentPkmnStrParam(int) const;
  virtual void setCurrentPkmnStrParam(int, const string &);

private:

  int _selectedPartyIndex;
  int _selectedMoveIndex;

  bool _isCreatingPkmn;
  bool _isChangingMove;

  PkmnSaveStateModel *_model;
  PkmnPartyView *_view;

};

#endif // PKMN_PARTY_CONTROLLER
