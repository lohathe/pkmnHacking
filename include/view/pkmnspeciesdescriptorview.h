#ifndef PKMN_SPECIES_DESCRIPTORVIEW
#define PKMN_SPECIES_DESCRIPTORVIEW

#include <QWidget>

class PkmnSpeciesDescriptorView : public QWidget {

  Q_OBJECT

public:

  PkmnSpeciesDescriptorView(QWidget *);

signals:

public slots:

  void displayDescriptionFor(int);

protected:

  virtual void paintEvent(QPaintEvent *);

private:

  int _displayedPkmnIndex;


};

#endif // PKMN_SPECIES_DESCRIPTOR_VIEW
