#ifndef PKMN_ELEMENT_PICKER_VIEW
#define PKMN_ELEMENT_PICKER_VIEW

#include <QAction>
#include <QMenu>
#include <QWidget>
#include <QObject>

class PkmnElementPickerAction : public QAction {

  Q_OBJECT

public:
  PkmnElementPickerAction(QObject *, int);
  int getElement() const;

signals:
  void elementActionTriggered(int);

private slots:
  void manageTriggered();

private:
  int _elementValue;

};

class PkmnElementPickerView : public QMenu {

  Q_OBJECT

public:
  PkmnElementPickerView(QWidget *);
  int getSelectedElement() const;

signals:
  void elementSelected(int);

};

#endif //PKMN_ELEMENT_PICKER_VIEW
