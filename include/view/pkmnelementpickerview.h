#ifndef PKMN_ELEMENT_PICKER_VIEW
#define PKMN_ELEMENT_PICKER_VIEW

#include <QComboBox>
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
  PkmnElementPickerView(QWidget *, bool allElements = true);

signals:
  void elementSelected(int);

};


class PkmnElementComboBox : public QComboBox {

  Q_OBJECT

public:
  PkmnElementComboBox(QWidget *, int);
  int getSelectedElement() const;
  void setSelectedElement(int);

signals:
  void elementSelected(int, int);

private slots:
  void manageSelection(int);

private:
  int _referredInfo;
  int getElementIdFromIndex(int) const;
  int getElementIndexFromId(int) const;

};

#endif //PKMN_ELEMENT_PICKER_VIEW
