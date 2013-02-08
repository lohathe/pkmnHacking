#include "pkmnsavestateview.h"
#include "pkmnpartyview.h"
#include "pkmnpokedexview.h"

#include <QString>
#include <QAction>
#include <QActionGroup>
#include <QToolButton>
#include <QVBoxLayout>

PkmnSaveStateView::PkmnSaveStateView () {

  _partyView = new PkmnPartyView(this);
  _pokedexView = new PkmnPokedexView(this);


  QWidget *placeholder = new QWidget(this);
  QVBoxLayout *placeholderLayout = new QVBoxLayout();
  placeholderLayout -> addWidget(_partyView);
  placeholderLayout -> addWidget(_pokedexView);
  placeholder -> setLayout(placeholderLayout);
  setCentralWidget(placeholder);

  _partyView -> setVisible(false);
  _pokedexView -> setVisible(false);


  createMyStatusBar();
  createMyToolBar();

  setWindowTitle("PkmnYellow Hacking");

  setFixedSize(800, 600);
  show();

}

void PkmnSaveStateView::createMyStatusBar() {

  _statusBar = statusBar();
  _statusBar -> setSizeGripEnabled(false);
/*  _statusImg = new QLabel(this);
  _statusBar -> addPermanentWidget(_statusImg);
  _statusMessage = new QLabel(this);
  _statusBar -> addPermanentWidget(_statusMessage, 1);

  _statusImg -> setPixmap(QPixmap(":/img/statusok.png").scaled(20, 20));
  _statusMessage -> setText("Application started correctly.");
  */
}

void PkmnSaveStateView::createMyToolBar() {

  _toolBar = addToolBar("Show");
  _toolBar -> setFloatable(false);
  _toolBar -> setMovable(false);

  QAction *saveToFile = new QAction(QIcon::fromTheme("document-save"), "Save", this);
  connect(saveToFile, SIGNAL(triggered()), this, SIGNAL(saveToFileEvent()));

  QActionGroup *showGroup = new QActionGroup(this);
  QAction *showParty = new QAction(QIcon(":/img/pokeballSprite.png"), "Party Pokemon", showGroup);
  showParty->setCheckable(true);
  connect(showParty, SIGNAL(toggled(bool)), _partyView, SLOT(setVisible(bool)));

  QAction *showPokedex = new QAction(QIcon(":/img/pokeballSprite.png"), "Pokedex", showGroup);
  showPokedex->setCheckable(true);
  connect(showPokedex, SIGNAL(toggled(bool)), _pokedexView, SLOT(setVisible(bool)));

  _toolBar -> addAction(saveToFile);
  _toolBar -> addSeparator();
  _toolBar -> addAction(showParty);
  _toolBar -> addAction(showPokedex);

}

void PkmnSaveStateView::manageOperationOutcome(bool outcome, const string &message) {

  QString msg = "";
  if (outcome)
    msg = "(1) ";
  else
    msg = "(0) ";
  msg += QString::fromStdString(message);
  _statusBar -> showMessage(msg, 5000);

/*
  if (outcome)
    _statusImg-> setPixmap(QPixmap(":/img/statusok.png").scaledToHeight(25));
  else
    _statusImg-> setPixmap(QPixmap(":/img/statusno.png").scaledToHeight(25));

  _statusMessage -> setText(QString::fromStdString(message));
*/
}

PkmnPartyView *PkmnSaveStateView::getPartyView() {
  return _partyView;
}

PkmnPokedexView *PkmnSaveStateView::getPokedexView() {
  return _pokedexView;
}
