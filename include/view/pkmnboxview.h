#ifndef PKMN_BOX_VIEW
#define PKMN_BOX_VIEW

#include <QWidget>

class PkmnSaveStateModel;

class PkmnBoxView : public QWidget {

  Q_OBJECT

public:

  PkmnBoxView (QWidget *);

  void setSelectedBox(int);
  void setSelectedBoxPkmn(int);
  void displayPkmnInfo();
  void displaySpeciesPicker();
  void displayMovePicker();

  void setCoherencyEnabled(bool);

signals:

public slots:

private:

  int _selectedBoxIndex;
  int _selectedPkmnIndex;

  PkmnSaveStateModel *_model;

};

#endif // PKMN_BOX_VIEW
