#ifndef PKMN_PARTY_CONTROLLER
#define PKMN_PARTY_CONTROLLER

#include <QObject>

class PkmnSaveStateModel;
class PkmnSaveStateView;

class PkmnPartyController : public QObject {

  Q_OBJECT

public:

  PkmnPartyController (PkmnSaveStateModel *, PkmnSaveStateView *);

signals:

public slots:

private slots:

private:

};

#endif // PKMN_PARTY_CONTROLLER
