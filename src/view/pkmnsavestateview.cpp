#include "pkmnsavestateview.h"
#include "pkmnpartyview.h"

PkmnSaveStateView::PkmnSaveStateView () {

  _partyView = new PkmnPartyView(this);
  _partyView -> setFixedSize(800, 600);

  _partyView -> setVisible(true);

  setFixedSize(800, 600);
  show();

}

PkmnPartyView *PkmnSaveStateView::getPartyView() {
  return _partyView;
}
