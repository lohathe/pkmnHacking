#include "pkmnsavestateview.h"
#include "pkmnpartyview.h"
#include "pkmnboxview.h"
#include "pkmnpokedexview.h"

#include <QString>
#include <QAction>
#include <QActionGroup>
#include <QToolButton>
#include <QVBoxLayout>
#include <QFileDialog>

PkmnSaveStateView::PkmnSaveStateView () {

  _partyView = new PkmnPartyView(this);
  _boxView = new PkmnBoxView(this);
  _pokedexView = new PkmnPokedexView(this);


  QWidget *placeholder = new QWidget(this);
  QVBoxLayout *placeholderLayout = new QVBoxLayout();
  placeholderLayout -> addWidget(_partyView);
  placeholderLayout -> addWidget(_boxView);
  placeholderLayout -> addWidget(_pokedexView);
  placeholder -> setLayout(placeholderLayout);
  setCentralWidget(placeholder);

  _partyView -> setVisible(false);
  _boxView -> setVisible(false);
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

  _toolBar = addToolBar("Main Toolbar");
  _toolBar -> setFloatable(false);
  _toolBar -> setMovable(false);

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

PkmnBoxView *PkmnSaveStateView::getBoxView() {
  return _boxView;
}

PkmnPokedexView *PkmnSaveStateView::getPokedexView() {
  return _pokedexView;
}

QToolBar *PkmnSaveStateView::getMainToolBar() {
  return _toolBar;
}
