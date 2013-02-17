#include "pkmnwidget.h"
#include "pkmnstate.h"

#include <QString>

// PKMN_SPIN_BOX

PkmnSpinBox::PkmnSpinBox (QWidget *parent, int referredInfo) :
  QSpinBox(parent), _referredInfo(referredInfo) {

  setMinimum(PkmnState::getMinValue(referredInfo));
  setMaximum(PkmnState::getMaxValue(referredInfo));

  connect(this, SIGNAL(valueChanged(int)),
          this, SLOT(manageValueChanged(int)));
}

void PkmnSpinBox::manageValueChanged(int newValue) {
  emit valueChanged(_referredInfo, newValue);
}

// PKMN_LINE_EDIT

PkmnLineEdit::PkmnLineEdit (QWidget *parent, int referredInfo) :
  QLineEdit(parent), _referredInfo(referredInfo) {

  //setMaxLength(10);

  connect(this, SIGNAL(editingFinished()),
          this, SLOT(manageEditingFinished()));
}

void PkmnLineEdit::manageEditingFinished() {
  emit valueChanged(_referredInfo, text().toStdString());
}

// PKMN_CHECK_BOX

PkmnCheckBox::PkmnCheckBox (QWidget *parent, int referredInfo, int referredValue) :
  QCheckBox(parent), _referredInfo(referredInfo), _referredValue(referredValue) {

  connect(this, SIGNAL(clicked()),
          this, SLOT(manageClicked()));
}

void PkmnCheckBox::manageClicked() {
  emit valueChanged(_referredInfo, _referredValue);
}

// PKMN_PUSH_BUTTON
PkmnPushButton::PkmnPushButton (QWidget *parent, int referredInfo) :
  QPushButton(parent), _referredInfo(referredInfo) {

  connect(this, SIGNAL(clicked()),
          this, SLOT(manageClicked()));
}

void PkmnPushButton::manageClicked() {
  emit buttonClicked(_referredInfo);
}

// PKMN_TOOL_BUTTON
PkmnToolButton::PkmnToolButton (QWidget *parent, int referredInfo) :
  QToolButton(parent), _referredInfo(referredInfo) {

  connect(this, SIGNAL(clicked()),
          this, SLOT(manageClicked()));
}

void PkmnToolButton::manageClicked() {
  emit buttonClicked(_referredInfo);
}

