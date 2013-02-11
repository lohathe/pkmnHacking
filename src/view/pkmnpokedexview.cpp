#include "pkmnpokedexview.h"
#include "pkmnspeciesdescriptorview.h"

#include "pkmnsavestatemodel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>

PkmnPokedexView::PkmnPokedexView (QWidget *parent) : QWidget(parent) {

  QVBoxLayout *layout = new QVBoxLayout();

  QWidget *listWidget = new QWidget(this);
  QVBoxLayout *scrollListLayout = new QVBoxLayout();
  PkmnSpeciesDescriptorView *s = new PkmnSpeciesDescriptorView(this);

  for (int i=0; i<151; i++) {
    _pkmnList[i] = new PkmnPokedexListItemView(i+1, listWidget);
    connect(_pkmnList[i], SIGNAL(clickedEvent(int)),
            this, SIGNAL(pkmnPokedexEntryClicked(int)));
    connect(_pkmnList[i], SIGNAL(displayInfoEvent(int)),
            s, SLOT(displayDescriptionFor(int)));
    scrollListLayout -> addWidget(_pkmnList[i]);
  }
  listWidget -> setLayout(scrollListLayout);

  QScrollArea *scrollArea = new QScrollArea(this);
  scrollArea -> setWidget(listWidget);
  scrollArea -> setWidgetResizable(true);

  QLabel *title = new QLabel("POKEDEX", this);
  title -> setStyleSheet("background:#000;color:#FFF;font-weight:bold;padding:3px 300px 3px 300px;");
  layout -> addWidget(title, 1, Qt::AlignHCenter);
  //layout -> addWidget(scrollArea, 20, Qt::AlignHCenter);
  //layout -> addStretch(100);

  QHBoxLayout *central = new QHBoxLayout();
  central->addWidget(scrollArea);
  central->addWidget(s);
  s->displayDescriptionFor(12);

  layout->addLayout(central, 20);

  setLayout(layout);

}

void PkmnPokedexView::connectModel(PkmnSaveStateModel *model) {

  _model = model;

  connect(_model, SIGNAL(changedPkmnPokedexEvent()),
          this, SLOT(updateList()));

  updateList();

}

void PkmnPokedexView::updateList() {

  PkmnPokedex pokedex = _model -> getPkmnPokedex();

  for (int i=0; i<151; ++i) {
    _pkmnList[i] -> updateItem(pokedex.isPkmnSeen(i+1), pokedex.isPkmnCatched(i+1));
  }

}
