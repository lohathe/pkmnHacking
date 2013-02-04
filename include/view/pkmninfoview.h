#ifndef PKMN_INFO_VIEW
#define PKMN_INFO_VIEW

#include "pkmnstate.h"
#include "pkmnwidget.h"

#include <string>
using std::string;

#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>

class PkmnInfoView : public QWidget {

  Q_OBJECT

public:

  PkmnInfoView (QWidget *);

  void updateInfo(const PkmnState *);

signals:

  void moveChangeEvent(int);
  void speciesChangeEvent();
  void pkmnParameterChangedEvent(int, int);
  void pkmnNameChangedEvent(const string &);

private:

  int scale;
  int imgDim;

  PkmnLineEdit *_pkmnName;
  PkmnSpinBox  *_pkmnLevel,
               *_pkmnExp,
               *_pkmnTrainer,
               *_hpev,
               *_attev,
               *_defev,
               *_spdev,
               *_spcev,
               *_ivhp,
               *_ivatt,
               *_ivdef,
               *_ivspd,
               *_ivspc,
               *_hp,
               *_maxhp,
               *_att,
               *_def,
               *_spd,
               *_spc,
               *_move1pp,
               *_move2pp,
               *_move3pp,
               *_move4pp,
               *_move1ppup,
               *_move2ppup,
               *_move3ppup,
               *_move4ppup;
  PkmnCheckBox *_alimentPsn,
               *_alimentSlp,
               *_alimentBrn,
               *_alimentFrz,
               *_alimentPrl;
  PkmnPushButton *_move1,
               *_move2,
               *_move3,
               *_move4;
  PkmnToolButton *_species;
  QLabel       *_speciesName,
               *_type1,
               *_type2;

  void organizeLayout(QVBoxLayout *);
  void organizeLayout(QGridLayout *);

};

#endif // PKMN_INFO_VIEW
