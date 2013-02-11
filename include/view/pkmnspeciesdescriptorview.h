#ifndef PKMN_SPECIES_DESCRIPTORVIEW
#define PKMN_SPECIES_DESCRIPTORVIEW

#include <QWidget>

#include <vector>
using std::vector;

class PkmnSpeciesDescriptorView : public QWidget {

  Q_OBJECT

public:

  PkmnSpeciesDescriptorView(QWidget *);

signals:

public slots:

  void displayDescriptionFor(int);

protected:

  virtual void paintEvent(QPaintEvent *);
  virtual void mouseReleaseEvent(QMouseEvent *);

private:

  struct Link {
    Link(int x, int y, int dim, int info) {_x=x; _y=y; _dim=dim, _info=info;}
    int _x, _y, _dim, _info;
  };

  int _displayedPkmnIndex;
  vector<Link> _mouseLinks;

};

#endif // PKMN_SPECIES_DESCRIPTOR_VIEW
