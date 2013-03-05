#include "pkmninfoview.h"
#include "pkmnstate.h"
#include "pkmnaliment.h"
#include "pkmnelement.h"
#include "pkmnmove.h"
#include "pkmnspecies.h"

#include "pkmnelementpickerview.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

PkmnInfoView::PkmnInfoView (QWidget *parent)
  : QWidget(parent), _fullEnable(true) {

  scale = 2;
  imgDim = 56;

}

void PkmnInfoView::initializeWidgets() {
  _pkmnName    = new PkmnLineEdit(this, PKMNNAME);
  _pkmnName -> setMaxLength(10);
  _pkmnLevel   = new PkmnSpinBox(this, LEVEL);
  _pkmnExp     = new PkmnSpinBox(this, EXP);
  _pkmnTrainer = new PkmnSpinBox(this, TRAINER);
  _pkmnOTName = new PkmnLineEdit(this, OTNAME);
  _pkmnOTName -> setMaxLength(10);
  _hpev        = new PkmnSpinBox(this, HPEV);
  _attev       = new PkmnSpinBox(this, ATTEV);
  _defev       = new PkmnSpinBox(this, DEFEV);
  _spdev       = new PkmnSpinBox(this, SPDEV);
  _spcev       = new PkmnSpinBox(this, SPCEV);
  _ivhp        = new PkmnSpinBox(this, IV | HP);
  _ivatt       = new PkmnSpinBox(this, IV | ATT);
  _ivdef       = new PkmnSpinBox(this, IV | DEF);
  _ivspd       = new PkmnSpinBox(this, IV | SPD);
  _ivspc       = new PkmnSpinBox(this, IV | SPC);
  _ivhp -> setMaximum(15);
  _ivatt -> setMaximum(15);
  _ivdef -> setMaximum(15);
  _ivspd -> setMaximum(15);
  _ivspc -> setMaximum(15);
  _hp          = new PkmnSpinBox(this, HP);
  _maxhp       = new PkmnSpinBox(this, MAXHP);
  _att         = new PkmnSpinBox(this, ATT);
  _def         = new PkmnSpinBox(this, DEF);
  _spd         = new PkmnSpinBox(this, SPD);
  _spc         = new PkmnSpinBox(this, SPC);
  _move1pp     = new PkmnSpinBox(this, MOVE1PP);
  _move2pp     = new PkmnSpinBox(this, MOVE2PP);
  _move3pp     = new PkmnSpinBox(this, MOVE3PP);
  _move4pp     = new PkmnSpinBox(this, MOVE4PP);
  _move1pp -> setMaximum(63);
  _move2pp -> setMaximum(63);
  _move3pp -> setMaximum(63);
  _move4pp -> setMaximum(63);
  _move1ppup   = new PkmnSpinBox(this, IV | MOVE1PP);
  _move2ppup   = new PkmnSpinBox(this, IV | MOVE2PP);
  _move3ppup   = new PkmnSpinBox(this, IV | MOVE3PP);
  _move4ppup   = new PkmnSpinBox(this, IV | MOVE4PP);
  _move1ppup -> setMaximum(3);
  _move2ppup -> setMaximum(3);
  _move3ppup -> setMaximum(3);
  _move4ppup -> setMaximum(3);
  _alimentPsn  = new PkmnCheckBox(this, ALIMENT, Aliment::POISONED);
  _alimentSlp  = new PkmnCheckBox(this, ALIMENT, Aliment::ASLEEP);
  _alimentBrn  = new PkmnCheckBox(this, ALIMENT, Aliment::BURNED);
  _alimentFrz  = new PkmnCheckBox(this, ALIMENT, Aliment::FROZEN);
  _alimentPrl  = new PkmnCheckBox(this, ALIMENT, Aliment::PARALYZED);
  _alimentPsn -> setText(QString::fromStdString(Aliment::toString(Aliment::POISONED)));
  _alimentSlp -> setText(QString::fromStdString(Aliment::toString(Aliment::ASLEEP)));
  _alimentBrn -> setText(QString::fromStdString(Aliment::toString(Aliment::BURNED)));
  _alimentFrz -> setText(QString::fromStdString(Aliment::toString(Aliment::FROZEN)));
  _alimentPrl -> setText(QString::fromStdString(Aliment::toString(Aliment::PARALYZED)));
  _move1       = new PkmnPushButton(this, MOVE1);
  _move2       = new PkmnPushButton(this, MOVE2);
  _move3       = new PkmnPushButton(this, MOVE3);
  _move4       = new PkmnPushButton(this, MOVE4);
  _species = new PkmnToolButton(this, SPECIES);
  _species -> setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  _species -> setFixedSize(scale*imgDim+20, scale*imgDim+40);
  _species -> setIconSize(QSize(scale*imgDim, scale*imgDim));
  _type1 = new PkmnElementComboBox(this, TYPE1);
  _type2 = new PkmnElementComboBox(this, TYPE2);
}

void PkmnInfoView::connectWidgets() {
  connect(_pkmnName, SIGNAL(valueChanged(int, const string &)),
          this, SIGNAL(pkmnStrParamChangedEvent(int, const string &)));
  connect(_pkmnLevel, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_pkmnExp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_pkmnTrainer, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_pkmnOTName, SIGNAL(valueChanged(int, const string &)),
          this, SIGNAL(pkmnStrParamChangedEvent(int, const string &)));
  connect(_hpev, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_attev, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_defev, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_spdev, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_spcev, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_ivhp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_ivatt, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_ivdef, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_ivspd, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_ivspc, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_hp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_maxhp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_att, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_def, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_spd, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_spc, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move1pp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move2pp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move3pp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move4pp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move1ppup, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move2ppup, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move3ppup, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move4ppup, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_alimentPsn, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_alimentSlp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_alimentBrn, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_alimentFrz, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_alimentPrl, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move1, SIGNAL(buttonClicked(int)),
          this, SIGNAL(moveChangeEvent(int)));
  connect(_move2, SIGNAL(buttonClicked(int)),
          this, SIGNAL(moveChangeEvent(int)));
  connect(_move3, SIGNAL(buttonClicked(int)),
          this, SIGNAL(moveChangeEvent(int)));
  connect(_move4, SIGNAL(buttonClicked(int)),
          this, SIGNAL(moveChangeEvent(int)));
  connect(_species, SIGNAL(buttonClicked(int)),
          this, SIGNAL(speciesChangeEvent()));
  connect(_type1, SIGNAL(elementSelected(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_type2, SIGNAL(elementSelected(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
}

QLayout *PkmnInfoView::organizeLayoutGeneralInfo() {

  QGridLayout *result = new QGridLayout();

  result->addWidget(new QLabel("Nickname:",this), 0, 0, 1, 1, Qt::AlignRight);
  result->addWidget(_pkmnName, 0, 1, 1, 5);
  result->addWidget(new QLabel("Trainer:", this), 1, 0, 1, 1, Qt::AlignRight);
  result->addWidget(_pkmnTrainer, 1, 1, 1, 1);
  result->addWidget(new QLabel("OT Name:", this), 1, 2, 1, 1, Qt::AlignRight);
  result->addWidget(_pkmnOTName, 1, 3, 1, 3);
  result->addWidget(new QLabel("Lvl:", this), 2, 0, 1, 1, Qt::AlignRight);
  result->addWidget(_pkmnLevel,   2, 1, 1, 1);
  result->addWidget(new QLabel("Exp:", this), 2, 2, 1, 1, Qt::AlignRight);
  result->addWidget(_pkmnExp,     2, 3, 1, 3);
  result->addWidget(new QLabel("Aliment:", this), 3, 0, 1, 1, Qt::AlignRight);
  result->addWidget(_alimentPsn, 3, 1, 1, 1);
  result->addWidget(_alimentSlp, 3, 2, 1, 1);
  result->addWidget(_alimentBrn, 3, 3, 1, 1);
  result->addWidget(_alimentFrz, 3, 4, 1, 1);
  result->addWidget(_alimentPrl, 3, 5, 1, 1);
  //result->addWidget(_alimentFrz, 4, 1, 1, 1);
  //result->addWidget(_alimentPrl, 4, 2, 1, 1);
  //result->addWidget(_species, 0, 4, 5, 1);

  result->setColumnStretch(0, 1);
  result->setColumnStretch(1, 1);
  result->setColumnStretch(2, 1);
  result->setColumnStretch(3, 1);
  result->setColumnStretch(4, 1);
  result->setColumnStretch(5, 1);

  return result;

}

QLayout *PkmnInfoView::organizeLayoutSpecies() {

  QVBoxLayout *result = new QVBoxLayout();

  result -> addStretch(3);
  result -> addWidget(new QLabel("Species", this), 0, Qt::AlignHCenter);
  result -> addWidget(_species);
  result -> addStretch(1);
  result -> addWidget(new QLabel("Type 1", this), 0, Qt::AlignHCenter);
  result -> addWidget(_type1);
  result -> addWidget(new QLabel("Type 2", this), 0, Qt::AlignHCenter);
  result -> addWidget(_type2);
  result -> addStretch(3);

  return result;

}

QLayout *PkmnInfoView::organizeLayoutStatistics() {

  QGridLayout *result = new QGridLayout();

  result->addWidget(new QLabel("Value", this),   0, 2, 1, 3, Qt::AlignHCenter);
  result->addWidget(new QLabel("EV", this),      0, 5, 1, 1, Qt::AlignHCenter);
  result->addWidget(new QLabel("IV", this),      0, 6, 1, 1, Qt::AlignHCenter);
  result->addWidget(new QLabel("HP:", this),     1, 1, 1, 1, Qt::AlignRight);
  result->addWidget(new QLabel("ATT:", this),    2, 1, 1, 1, Qt::AlignRight);
  result->addWidget(new QLabel("DEF:", this),    3, 1, 1, 1, Qt::AlignRight);
  result->addWidget(new QLabel("SPD:", this),    4, 1, 1, 1, Qt::AlignRight);
  result->addWidget(new QLabel("SPC:", this),    5, 1, 1, 1, Qt::AlignRight);
  result->addWidget(_hp,     1, 2, 1, 1);
  result->addWidget(new QLabel("/", this), 1, 3, 1, 1);
  result->addWidget(_maxhp,  1, 4, 1, 1);
  result->addWidget(_att,    2, 2, 1, 3);
  result->addWidget(_def,    3, 2, 1, 3);
  result->addWidget(_spd,    4, 2, 1, 3);
  result->addWidget(_spc,    5, 2, 1, 3);
  result->addWidget(_hpev,   1, 5, 1, 1);
  result->addWidget(_attev,  2, 5, 1, 1);
  result->addWidget(_defev,  3, 5, 1, 1);
  result->addWidget(_spdev,  4, 5, 1, 1);
  result->addWidget(_spcev,  5, 5, 1, 1);
  result->addWidget(_ivhp,   1, 6, 1, 1);
  result->addWidget(_ivatt,  2, 6, 1, 1);
  result->addWidget(_ivdef,  3, 6, 1, 1);
  result->addWidget(_ivspd,  4, 6, 1, 1);
  result->addWidget(_ivspc,  5, 6, 1, 1);

  result->setColumnStretch(0, 0);
  result->setColumnStretch(1, 1);
  result->setColumnStretch(2, 2);
  result->setColumnStretch(3, 0);
  result->setColumnStretch(4, 2);
  result->setColumnStretch(5, 3);
  result->setColumnStretch(6, 1);

  return result;

}

QLayout *PkmnInfoView::organizeLayoutMoves() {

  QGridLayout *result = new QGridLayout();

  result->addWidget(new QLabel("Move", this), 0, 1, 1, 1, Qt::AlignHCenter);
  result->addWidget(new QLabel("PP", this),   0, 2, 1, 1, Qt::AlignHCenter);
  result->addWidget(new QLabel("PPUP", this), 0, 3, 1, 1, Qt::AlignHCenter);
  result->addWidget(_move1,     1, 1, 1, 1);
  result->addWidget(_move2,     2, 1, 1, 1);
  result->addWidget(_move3,     3, 1, 1, 1);
  result->addWidget(_move4,     4, 1, 1, 1);
  result->addWidget(_move1pp,   1, 2, 1, 1);
  result->addWidget(_move2pp,   2, 2, 1, 1);
  result->addWidget(_move3pp,   3, 2, 1, 1);
  result->addWidget(_move4pp,   4, 2, 1, 1);
  result->addWidget(_move1ppup, 1, 3, 1, 1);
  result->addWidget(_move2ppup, 2, 3, 1, 1);
  result->addWidget(_move3ppup, 3, 3, 1, 1);
  result->addWidget(_move4ppup, 4, 3, 1, 1);

  result->setColumnStretch(0, 1);
  result->setColumnStretch(1, 6);
  result->setColumnStretch(2, 1);
  result->setColumnStretch(3, 1);

  return result;

}

void PkmnInfoView::updateInfo(const PkmnState info) {

  if (!info.isValid()) {
    _pkmnName    -> setText("---");
    _pkmnOTName  -> setText("---");
    _pkmnLevel   -> setValue(1);
    _pkmnExp     -> setValue(1);
    _pkmnTrainer -> setValue(0);
    _hpev        -> setValue(0);
    _attev       -> setValue(0);
    _defev       -> setValue(0);
    _spdev       -> setValue(0);
    _spcev       -> setValue(0);
    _ivhp        -> setValue(0);
    _ivatt       -> setValue(0);
    _ivdef       -> setValue(0);
    _ivspd       -> setValue(0);
    _ivspc       -> setValue(0);
    _hp          -> setValue(1);
    _maxhp       -> setValue(1);
    _att         -> setValue(1);
    _def         -> setValue(1);
    _spd         -> setValue(1);
    _spc         -> setValue(1);
    _move1pp     -> setValue(0);
    _move2pp     -> setValue(0);
    _move3pp     -> setValue(0);
    _move4pp     -> setValue(0);
    _move1ppup   -> setValue(0);
    _move2ppup   -> setValue(0);
    _move3ppup   -> setValue(0);
    _move4ppup   -> setValue(0);
    _alimentPsn  -> setChecked(false);
    _alimentSlp  -> setChecked(false);
    _alimentBrn  -> setChecked(false);
    _alimentFrz  -> setChecked(false);
    _alimentPrl  -> setChecked(false);
    _move1       -> setText("No move");
    _move2       -> setText("No move");
    _move3       -> setText("No move");
    _move4       -> setText("No move");
    _species     -> setIcon(QPixmap(":/img/pokeballSprite.png")
                            .copy(0, 0, imgDim, imgDim)
                            .scaled(scale*imgDim, scale*imgDim));
    QString speciesname = "---";
    _species     -> setText(speciesname);

    enableAuthorized(false);
  } else {
    _pkmnName    -> setText(QString::fromStdString(info.getStr(PKMNNAME)));
    _pkmnOTName  -> setText(QString::fromStdString(info.getStr(OTNAME)));
    _pkmnLevel   -> setValue(info.get(LEVEL));
    _pkmnExp     -> setValue(info.get(EXP));
    _pkmnTrainer -> setValue(info.get(TRAINER));
    _hpev        -> setValue(info.get(HPEV));
    _attev       -> setValue(info.get(ATTEV));
    _defev       -> setValue(info.get(DEFEV));
    _spdev       -> setValue(info.get(SPDEV));
    _spcev       -> setValue(info.get(SPCEV));
    _ivhp        -> setValue(((info.get(IV)>>9)&0x08)|((info.get(IV)>>6)&0x04)|((info.get(IV)>>3)&0x02)|((info.get(IV)>>0)&0x01));
    _ivatt       -> setValue((info.get(IV)>>12)& 0x000F);
    _ivdef       -> setValue((info.get(IV)>>8) & 0x000F);
    _ivspd       -> setValue((info.get(IV)>>4) & 0x000F);
    _ivspc       -> setValue((info.get(IV)>>0) & 0x000F);
    _hp          -> setValue(info.get(HP));
    _maxhp       -> setValue(info.get(MAXHP));
    _att         -> setValue(info.get(ATT));
    _def         -> setValue(info.get(DEF));
    _spd         -> setValue(info.get(SPD));
    _spc         -> setValue(info.get(SPC));
    _move1pp     -> setValue(info.get(MOVE1PP)&0x3F);
    _move2pp     -> setValue(info.get(MOVE2PP)&0x3F);
    _move3pp     -> setValue(info.get(MOVE3PP)&0x3F);
    _move4pp     -> setValue(info.get(MOVE4PP)&0x3F);
    _move1ppup   -> setValue((info.get(MOVE1PP)&0xC0)>>6);
    _move2ppup   -> setValue((info.get(MOVE2PP)&0xC0)>>6);
    _move3ppup   -> setValue((info.get(MOVE3PP)&0xC0)>>6);
    _move4ppup   -> setValue((info.get(MOVE4PP)&0xC0)>>6);
    _alimentPsn  -> setChecked(info.get(ALIMENT)&Aliment::POISONED);
    _alimentSlp  -> setChecked(info.get(ALIMENT)&Aliment::ASLEEP);
    _alimentBrn  -> setChecked(info.get(ALIMENT)&Aliment::BURNED);
    _alimentFrz  -> setChecked(info.get(ALIMENT)&Aliment::FROZEN);
    _alimentPrl  -> setChecked(info.get(ALIMENT)&Aliment::PARALYZED);
    _move1       -> setText(QString::fromStdString(PkmnMoveList::get(info.get(MOVE1))->getName()));
    _move2       -> setText(QString::fromStdString(PkmnMoveList::get(info.get(MOVE2))->getName()));
    _move3       -> setText(QString::fromStdString(PkmnMoveList::get(info.get(MOVE3))->getName()));
    _move4       -> setText(QString::fromStdString(PkmnMoveList::get(info.get(MOVE4))->getName()));
    const PkmnSpecies *species = PkmnSpeciesList::getById(info.get(SPECIES));
    _species     -> setIcon(QPixmap(":/img/spritesyellowcolor.png")
                            .copy(1+((species->getIndex()-1)%12)*(imgDim+1),
                                  1+((species->getIndex()-1)/12)*(imgDim+1),
                                  imgDim,
                                  imgDim)
                            .scaled(scale*imgDim, scale*imgDim));
    QString speciesname = QString::fromStdString(species->getName());
    _species     -> setText(speciesname);
    _type1 -> setSelectedElement(info.get(TYPE1));
    _type2 -> setSelectedElement(info.get(TYPE2));

    enableAuthorized(true);
  }

}

void PkmnInfoView::setAuthorizationEnable(bool authorization) {
  if (authorization == _fullEnable)
    return;
  _fullEnable = authorization;
  enableAuthorized(this -> isEnabled());
}


PkmnInfoViewParty::PkmnInfoViewParty (QWidget *parent) : PkmnInfoView(parent) {

  initializeWidgets();
  connectWidgets();

  QVBoxLayout *middleV = new QVBoxLayout();
  middleV -> addLayout(organizeLayoutStatistics());
  middleV -> addLayout(organizeLayoutMoves());

  QHBoxLayout *middleH = new QHBoxLayout();
  middleH -> addLayout(middleV);
  middleH -> addSpacing(20);
  middleH -> addLayout(organizeLayoutSpecies());

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout -> addLayout(organizeLayoutGeneralInfo());
  layout -> addLayout(middleH);
  layout -> addStretch(1);

  updateInfo(PkmnState(NULL, NULL, NULL));
  setLayout(layout);

}
void PkmnInfoViewParty::enableAuthorized(bool enable) {

  setEnabled(enable);

  if (enable) {
    _type1 -> setEnabled(_fullEnable);
    _type2 -> setEnabled(_fullEnable);
    _maxhp -> setEnabled(_fullEnable);
    _att   -> setEnabled(_fullEnable);
    _def   -> setEnabled(_fullEnable);
    _spd   -> setEnabled(_fullEnable);
    _spc   -> setEnabled(_fullEnable);
  }

}

PkmnInfoViewBox::PkmnInfoViewBox(QWidget *parent) : PkmnInfoView(parent) {

  initializeWidgets();
  connectWidgets();

  QHBoxLayout *upperH = new QHBoxLayout();
  upperH -> addStretch(1);
  upperH -> addLayout(organizeLayoutSpecies());
  upperH -> addLayout(organizeLayoutGeneralInfo());
  upperH -> addStretch(1);

  QHBoxLayout *lowerH = new QHBoxLayout();
  lowerH -> addLayout(organizeLayoutStatistics());
  lowerH -> addLayout(organizeLayoutMoves());

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout -> addLayout(upperH);
  layout -> addLayout(lowerH);
  layout -> addStretch(1);

  updateInfo(PkmnState(NULL, NULL, NULL));
  setLayout(layout);

}
void PkmnInfoViewBox::enableAuthorized(bool enable) {

  setEnabled(enable);

  if (enable) {
    _type1 -> setEnabled(_fullEnable);
    _type2 -> setEnabled(_fullEnable);
  }
  _maxhp -> setEnabled(false);
  _att   -> setEnabled(false);
  _def   -> setEnabled(false);
  _spd   -> setEnabled(false);
  _spc   -> setEnabled(false);

}
QLayout *PkmnInfoViewBox::organizeLayoutSpecies() {

  QVBoxLayout *rightV = new QVBoxLayout();
  rightV -> addStretch(1);
  rightV -> addWidget(new QLabel("Type 1", this), 0, Qt::AlignHCenter);
  rightV -> addWidget(_type1);
  rightV -> addWidget(new QLabel("Type 2", this), 0, Qt::AlignHCenter);
  rightV -> addWidget(_type2);
  rightV -> addStretch(1);

  QHBoxLayout *result = new QHBoxLayout();
  result -> addWidget(_species);
  result -> addLayout(rightV);

  return result;

}
