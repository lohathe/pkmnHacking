#include "pkmnpokedexview.h"
#include "pkmnpokedexlistitemview.h"

#include "pkmnsavestatemodel.h"

#include <QVBoxLayout>
#include <QLabel>

PkmnPokedexView::PkmnPokedexView (QWidget *parent) : QWidget(parent) {

  QVBoxLayout *layout = new QVBoxLayout();

  layout -> addWidget(new QLabel("POKEDEX", this), Qt::AlignHCenter);
  layout -> addWidget(new PkmnPokedexListItemView(1, this));
  layout -> addWidget(new PkmnPokedexListItemView(2, this));
  layout -> addWidget(new PkmnPokedexListItemView(3, this));
  layout -> addWidget(new PkmnPokedexListItemView(4, this));
  layout -> addStretch(1);

  setLayout(layout);

}

void PkmnPokedexView::connectModel(PkmnSaveStateModel *model) {
  _model = model;
}
