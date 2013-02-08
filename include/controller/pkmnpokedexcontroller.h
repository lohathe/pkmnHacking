#ifndef PKMNPOKEDEXCONTROLLER_H
#define PKMNPOKEDEXCONTROLLER_H

#include <QObject>

#include <string>
using std::string;

class PkmnSaveStateModel;
class PkmnPokedexView;

class PkmnPokedexController : public QObject
{
  Q_OBJECT
public:

  PkmnPokedexController(PkmnSaveStateModel *, PkmnPokedexView *);
  
signals:

  void operationOutcomeEvent (bool, const string &);
  
public slots:

  void managePkmnPokedexEntryClicked(int);

private:

  PkmnSaveStateModel *_model;
  PkmnPokedexView *_view;
  
};

#endif // PKMNPOKEDEXCONTROLLER_H
