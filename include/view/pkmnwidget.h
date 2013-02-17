#ifndef PKMN_WIDGET
#define PKMN_WIDGET

#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QToolButton>
#include <QWidget>

#include <string>
using std::string;

class PkmnSpinBox : public QSpinBox {

  Q_OBJECT

public:
  PkmnSpinBox (QWidget *, int);

signals:
  void valueChanged(int, int);

private slots:
  void manageValueChanged(int);

private:
  int _referredInfo;

};

class PkmnLineEdit : public QLineEdit {

  Q_OBJECT

public:
  PkmnLineEdit (QWidget *, int);

signals:
  void valueChanged(int, const string &);

private slots:
  void manageEditingFinished();

private:
  int _referredInfo;

};

class PkmnCheckBox : public QCheckBox {

  Q_OBJECT

public:
  PkmnCheckBox (QWidget *, int, int);

signals:
  void valueChanged(int, int);

private slots:
  void manageClicked();

private:
  int _referredInfo;
  int _referredValue;

};

class PkmnPushButton : public QPushButton {

  Q_OBJECT

public:
  PkmnPushButton (QWidget *, int);

signals:
  void buttonClicked(int);

private slots:
  void manageClicked();

private:
  int _referredInfo;

};

class PkmnToolButton : public QToolButton {

  Q_OBJECT

public:
  PkmnToolButton (QWidget *, int);

signals:
  void buttonClicked(int);

private slots:
  void manageClicked();

private:
  int _referredInfo;

};

#endif // PKMNWIDGET_H
