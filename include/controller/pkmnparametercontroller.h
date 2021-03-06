#ifndef PKMN_PARAMETER_CONTROLLER
#define PKMN_PARAMETER_CONTROLLER

#include <string>
using std::string;

#include <QObject>

#include "pkmnspeciesdescriptor.h"
#include "pkmnstate.h"

class PkmnParameterController : public QObject {

  Q_OBJECT

public:

signals:

  void operationOutcomeEvent (bool, const string &);

public slots:

  virtual void manageEnableCoherency(bool);

  virtual void managePkmnStrParamChanged(int, const string &);
  virtual void managePkmnParamChanged(int, int);

protected:

  PkmnParameterController(bool);

  bool _coherencyEnabled;

  virtual const PkmnSpeciesDescriptor *getCurrentPkmnSpeciesDescriptor() const = 0;

  virtual bool isCurrentPkmnValid() const = 0;

  virtual const PkmnState getCurrentPkmnInfo() const = 0;

  virtual int getCurrentPkmnParam(int) const = 0;
  virtual void setCurrentPkmnParam(int, int) = 0;

  virtual string getCurrentPkmnStrParam(int) const = 0;
  virtual void setCurrentPkmnStrParam(int, const string &) = 0;

  virtual void manageParamIV(int, int);
  virtual void manageParamHP(int, int);
  virtual void manageParamLvl(int, int);
  virtual void manageParamExp(int, int);
  virtual void manageParamEV(int, int);
  virtual void manageParamSpecies(int, int);
  virtual void manageParamAliment(int, int);
  virtual void manageParamPP(int, int);

  virtual void setPkmnBasicStats();

private:

  int roundToNearestValue(int, int, int) const;
  void updateStatsValue(const PkmnSpeciesDescriptor *, const PkmnState, int);

};


#endif // PKMN_PARAMETER_CONTROLLER
