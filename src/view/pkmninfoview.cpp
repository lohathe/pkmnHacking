#include "pkmninfoview.h"
#include "pkmnstate.h"
#include "pkmnaliment.h"
#include "pkmnelement.h"
#include "pkmnmove.h"
#include "pkmnspecies.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

PkmnInfoView::PkmnInfoView (QWidget *parent) : QWidget(parent) {

  scale = 2;
  imgDim = 56;

  _pkmnName    = new PkmnLineEdit(this, NAME);
  _pkmnName -> setMaxLength(10);
  connect(_pkmnName, SIGNAL(valueChanged(const string &)),
          this, SIGNAL(pkmnNameChangedEvent(const string &)));

  _pkmnLevel   = new PkmnSpinBox(this, LEVEL);
  connect(_pkmnLevel, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  _pkmnExp     = new PkmnSpinBox(this, EXP);
  connect(_pkmnExp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));

  _pkmnTrainer = new PkmnSpinBox(this, TRAINER);
  connect(_pkmnTrainer, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));

  _hpev        = new PkmnSpinBox(this, HPEV);
  _attev       = new PkmnSpinBox(this, ATTEV);
  _defev       = new PkmnSpinBox(this, DEFEV);
  _spdev       = new PkmnSpinBox(this, SPDEV);
  _spcev       = new PkmnSpinBox(this, SPCEV);
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

  _hp          = new PkmnSpinBox(this, HP);
  _maxhp       = new PkmnSpinBox(this, MAXHP);
  _att         = new PkmnSpinBox(this, ATT);
  _def         = new PkmnSpinBox(this, DEF);
  _spd         = new PkmnSpinBox(this, SPD);
  _spc         = new PkmnSpinBox(this, SPC);
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

  _move1pp     = new PkmnSpinBox(this, MOVE1PP);
  _move2pp     = new PkmnSpinBox(this, MOVE2PP);
  _move3pp     = new PkmnSpinBox(this, MOVE3PP);
  _move4pp     = new PkmnSpinBox(this, MOVE4PP);
  _move1pp -> setMaximum(63);
  _move2pp -> setMaximum(63);
  _move3pp -> setMaximum(63);
  _move4pp -> setMaximum(63);
  connect(_move1pp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move2pp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move3pp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move4pp, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));

  _move1ppup   = new PkmnSpinBox(this, IV | MOVE1PP);
  _move2ppup   = new PkmnSpinBox(this, IV | MOVE2PP);
  _move3ppup   = new PkmnSpinBox(this, IV | MOVE3PP);
  _move4ppup   = new PkmnSpinBox(this, IV | MOVE4PP);
  _move1ppup -> setMaximum(3);
  _move2ppup -> setMaximum(3);
  _move3ppup -> setMaximum(3);
  _move4ppup -> setMaximum(3);
  connect(_move1ppup, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move2ppup, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move3ppup, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));
  connect(_move4ppup, SIGNAL(valueChanged(int,int)),
          this, SIGNAL(pkmnParameterChangedEvent(int,int)));

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

  _move1       = new PkmnPushButton(this, MOVE1);
  _move2       = new PkmnPushButton(this, MOVE2);
  _move3       = new PkmnPushButton(this, MOVE3);
  _move4       = new PkmnPushButton(this, MOVE4);
  connect(_move1, SIGNAL(buttonClicked(int)),
          this, SIGNAL(moveChangeEvent(int)));
  connect(_move2, SIGNAL(buttonClicked(int)),
          this, SIGNAL(moveChangeEvent(int)));
  connect(_move3, SIGNAL(buttonClicked(int)),
          this, SIGNAL(moveChangeEvent(int)));
  connect(_move4, SIGNAL(buttonClicked(int)),
          this, SIGNAL(moveChangeEvent(int)));

  _species     = new PkmnToolButton(this, SPECIES);
  _species -> setFixedSize(scale*imgDim+3, scale*imgDim+50);
  _species -> setIconSize(QSize(scale*imgDim, scale*imgDim));
  connect(_species, SIGNAL(buttonClicked(int)),
          this, SIGNAL(speciesChangeEvent()));

  //_speciesName = new QLabel(this);
  //_type1       = new QLabel(this);
  //_type2       = new QLabel(this);

  QGridLayout *layout = new QGridLayout(this);
  //QVBoxLayout *layout = new QVBoxLayout(this);
  organizeLayout(layout);

  updateInfo(NULL);
  setLayout(layout);

}

void PkmnInfoView::organizeLayout(QGridLayout *layout) {

  layout->addWidget(new QLabel("Nickname:", this), 0, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(_pkmnName,    0, 1, 1, 3);
  layout->addWidget(new QLabel("Trainer:", this), 0, 4, 1, 1, Qt::AlignRight);
  layout->addWidget(_pkmnTrainer, 0, 5, 1, 1);
  layout->addWidget(new QLabel("Lvl:", this), 1, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(_pkmnLevel,   1, 1, 1, 3);
  layout->addWidget(new QLabel("Exp:", this), 1, 4, 1, 1, Qt::AlignRight);
  layout->addWidget(_pkmnExp,     1, 5, 1, 1);

  layout->addWidget(_species,     2, 0, 5, 1);
  layout->addWidget(new QLabel("PP", this),   2, 4, 1, 1);
  layout->addWidget(new QLabel("PPUP", this), 2, 5, 1, 1);
  layout->addWidget(_move1,       3, 1, 1, 3);
  layout->addWidget(_move2,       4, 1, 1, 3);
  layout->addWidget(_move3,       5, 1, 1, 3);
  layout->addWidget(_move4,       6, 1, 1, 3);
  layout->addWidget(_move1pp,     3, 4, 1, 1);
  layout->addWidget(_move2pp,     4, 4, 1, 1);
  layout->addWidget(_move3pp,     5, 4, 1, 1);
  layout->addWidget(_move4pp,     6, 4, 1, 1);
  layout->addWidget(_move1ppup,   3, 5, 1, 1);
  layout->addWidget(_move2ppup,   4, 5, 1, 1);
  layout->addWidget(_move3ppup,   5, 5, 1, 1);
  layout->addWidget(_move4ppup,   6, 5, 1, 1);
  //layout->addWidget(_speciesName, );
  //layout->addWidget(_type1);
  //layout->addWidget(_type2);

  layout->addWidget(new QLabel("Value", this),   8, 1, 1, 3);
  layout->addWidget(new QLabel("EV", this),      8, 4, 1, 1);
  layout->addWidget(new QLabel("IV", this),      8, 5, 1, 1);
  layout->addWidget(new QLabel("HP:", this),     9, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(new QLabel("ATT:", this),   10, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(new QLabel("DEF:", this),   11, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(new QLabel("SPD:", this),   12, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(new QLabel("SPC:", this),   13, 0, 1, 1, Qt::AlignRight);
  layout->addWidget(_hp,     9, 1, 1, 1);
  layout->addWidget(new QLabel("/", this), 9, 2, 1, 1);
  layout->addWidget(_maxhp,  9, 3, 1, 1);
  layout->addWidget(_att,   10, 1, 1, 3);
  layout->addWidget(_def,   11, 1, 1, 3);
  layout->addWidget(_spd,   12, 1, 1, 3);
  layout->addWidget(_spc,   13, 1, 1, 3);
  layout->addWidget(_hpev,   9, 4, 1, 1);
  layout->addWidget(_attev, 10, 4, 1, 1);
  layout->addWidget(_defev, 11, 4, 1, 1);
  layout->addWidget(_spdev, 12, 4, 1, 1);
  layout->addWidget(_spcev, 13, 4, 1, 1);
  layout->addWidget(_ivhp,   9, 5, 1, 1);
  layout->addWidget(_ivatt, 10, 5, 1, 1);
  layout->addWidget(_ivdef, 11, 5, 1, 1);
  layout->addWidget(_ivspd, 12, 5, 1, 1);
  layout->addWidget(_ivspc, 13, 5, 1, 1);

  QHBoxLayout *layoutH = new QHBoxLayout();
  layoutH->addWidget(_alimentPsn);
  layoutH->addWidget(_alimentSlp);
  layoutH->addWidget(_alimentBrn);
  layoutH->addWidget(_alimentFrz);
  layoutH->addWidget(_alimentPrl);

  layout->addLayout(layoutH, 14, 0, 1, 6);
}

void PkmnInfoView::organizeLayout(QVBoxLayout *layout) {
  layout->addWidget(_species);
  layout->addWidget(_speciesName);
  layout->addWidget(_type1);
  layout->addWidget(_type2);
  layout->addWidget(_pkmnName);
  layout->addWidget(_pkmnTrainer);
  layout->addWidget(_pkmnLevel);
  layout->addWidget(_pkmnExp);

  layout->addWidget(_hpev);
  layout->addWidget(_attev);
  layout->addWidget(_defev);
  layout->addWidget(_spdev);
  layout->addWidget(_spcev);
  layout->addWidget(_ivhp);
  layout->addWidget(_ivatt);
  layout->addWidget(_ivdef);
  layout->addWidget(_ivspd);
  layout->addWidget(_ivspc);
  layout->addWidget(_hp);
  layout->addWidget(_maxhp);
  layout->addWidget(_att);
  layout->addWidget(_def);
  layout->addWidget(_spd);
  layout->addWidget(_spc);
  layout->addWidget(_move1pp);
  layout->addWidget(_move2pp);
  layout->addWidget(_move3pp);
  layout->addWidget(_move4pp);
  layout->addWidget(_move1ppup);
  layout->addWidget(_move2ppup);
  layout->addWidget(_move3ppup);
  layout->addWidget(_move4ppup);
  layout->addWidget(_alimentPsn);
  layout->addWidget(_alimentSlp);
  layout->addWidget(_alimentBrn);
  layout->addWidget(_alimentFrz);
  layout->addWidget(_alimentPrl);
  layout->addWidget(_move1);
  layout->addWidget(_move2);
  layout->addWidget(_move3);
  layout->addWidget(_move4);
}

void PkmnInfoView::updateInfo(const PkmnState *info) {

  if (info == NULL) {
    _pkmnName    -> setText("---");
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
    QString speciesname = "---\n---/---";
    _species     -> setText(speciesname);
    //_speciesName -> setText("---");
    //_type1       -> setText("---");
    //_type2       -> setText("---");

    setEnabled(false);
  } else {
    _pkmnName    -> setText(QString::fromStdString(info->getName()));
    _pkmnLevel   -> setValue(info->get(LEVEL));
    _pkmnExp     -> setValue(info->get(EXP));
    _pkmnTrainer -> setValue(info->get(TRAINER));
    _hpev        -> setValue(info->get(HPEV));
    _attev       -> setValue(info->get(ATTEV));
    _defev       -> setValue(info->get(DEFEV));
    _spdev       -> setValue(info->get(SPDEV));
    _spcev       -> setValue(info->get(SPCEV));
    _ivhp        -> setValue(((info->get(IV)>>9)&0x08)|((info->get(IV)>>6)&0x04)|((info->get(IV)>>3)&0x02)|((info->get(IV)>>0)&0x01));
    _ivatt       -> setValue((info->get(IV)>>12)& 0x000F);
    _ivdef       -> setValue((info->get(IV)>>8) & 0x000F);
    _ivspd       -> setValue((info->get(IV)>>4) & 0x000F);
    _ivspc       -> setValue((info->get(IV)>>0) & 0x000F);
    _hp          -> setValue(info->get(HP));
    _maxhp       -> setValue(info->get(MAXHP));
    _att         -> setValue(info->get(ATT));
    _def         -> setValue(info->get(DEF));
    _spd         -> setValue(info->get(SPD));
    _spc         -> setValue(info->get(SPC));
    _move1pp     -> setValue(info->get(MOVE1PP)&0x3F);
    _move2pp     -> setValue(info->get(MOVE2PP)&0x3F);
    _move3pp     -> setValue(info->get(MOVE3PP)&0x3F);
    _move4pp     -> setValue(info->get(MOVE4PP)&0x3F);
    _move1ppup   -> setValue((info->get(MOVE1PP)&0xC0)>>6);
    _move2ppup   -> setValue((info->get(MOVE2PP)&0xC0)>>6);
    _move3ppup   -> setValue((info->get(MOVE3PP)&0xC0)>>6);
    _move4ppup   -> setValue((info->get(MOVE4PP)&0xC0)>>6);
    _alimentPsn  -> setChecked(info->get(ALIMENT)&Aliment::POISONED);
    _alimentSlp  -> setChecked(info->get(ALIMENT)&Aliment::ASLEEP);
    _alimentBrn  -> setChecked(info->get(ALIMENT)&Aliment::BURNED);
    _alimentFrz  -> setChecked(info->get(ALIMENT)&Aliment::FROZEN);
    _alimentPrl  -> setChecked(info->get(ALIMENT)&Aliment::PARALYZED);
    _move1       -> setText(QString::fromStdString(PkmnMoveList::get(info->get(MOVE1))->getName()));
    _move2       -> setText(QString::fromStdString(PkmnMoveList::get(info->get(MOVE2))->getName()));
    _move3       -> setText(QString::fromStdString(PkmnMoveList::get(info->get(MOVE3))->getName()));
    _move4       -> setText(QString::fromStdString(PkmnMoveList::get(info->get(MOVE4))->getName()));
    const PkmnSpecies *species = PkmnSpeciesList::get(info->get(SPECIES));
    _species     -> setIcon(QPixmap(":/img/spritesyellowcolor.png")
                            .copy(1+((species->getIndex()-1)%12)*(imgDim+1),
                                  1+((species->getIndex()-1)/12)*(imgDim+1),
                                  imgDim,
                                  imgDim)
                            .scaled(scale*imgDim, scale*imgDim));
    QString speciesname = QString::fromStdString(species->getName()) + "\n" +
        QString::fromStdString(Element::toString(species->getElement1())) + "/" +
        QString::fromStdString(Element::toString(species->getElement2()));
    _species     -> setText(speciesname);
    //_speciesName -> setText(QString::fromStdString(species->getName()));
    //_type1       -> setText(QString::fromStdString(Element::toString(species->getElement1())));
    //_type2       -> setText(QString::fromStdString(Element::toString(species->getElement2())));

    setEnabled(true);
  }

}
