#ifndef PKMN_SPECIES_PICKER_VIEW
#define PKMN_SPECIES_PICKER_VIEW

#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

class PkmnSpeciesPickerView : public QWidget {

  Q_OBJECT

public:

  PkmnSpeciesPickerView (QWidget *);

signals:

  void speciesSelected (int);

public slots:

  void selectByElement (int);

private:

  QToolButton *_pkmns[151];
  QGridLayout *_layout;

};

#endif // PKMN_SPECIES_PICKER_VIEW
