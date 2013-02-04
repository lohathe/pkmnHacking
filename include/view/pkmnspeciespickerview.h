#ifndef PKMN_SPECIES_PICKER_VIEW
#define PKMN_SPECIES_PICKER_VIEW

#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QToolButton>
#include <QGridLayout>

class PkmnElementSelectorAction : public QAction {
  Q_OBJECT
public:
  PkmnElementSelectorAction(QObject *, int);
signals:
  void elementActionTriggered(int);
private slots:
  void manageTriggered();
private:
  int _elementValue;
};

class PkmnSpeciesPickerView : public QWidget {

  Q_OBJECT

public:

  PkmnSpeciesPickerView (QWidget *);

signals:

  void speciesSelected (int);

public slots:

  void selectByElement (int);

private:

  QMenu *createElementMenu();

  QToolButton *_pkmns[151];
  QGridLayout *_layout;

};

#endif // PKMN_SPECIES_PICKER_VIEW
