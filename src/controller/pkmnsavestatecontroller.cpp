#include "pkmnsavestatecontroller.h"
#include "pkmnpartycontroller.h"
#include "pkmnboxcontroller.h"
#include "pkmnpokedexcontroller.h"

#include "pkmnsavestatemodel.h"
#include "pkmnsavestate.h"

#include "pkmnsavestateview.h"
#include "pkmnpartyview.h"
#include "pkmnboxview.h"
#include "pkmnpokedexview.h"

#include <string>
using std::string;

#include <QAction>
#include <QActionGroup>
#include <QFileDialog>
#include <QToolBar>

PkmnSaveStateController::PkmnSaveStateController (string filepath) {

  _model = new PkmnSaveStateModel(new PkmnSaveState(filepath, false));
  _view = new PkmnSaveStateView();

  // CREATION OF SUB-CONTROLLERS
  _partyController = new PkmnPartyController(_model, _view->getPartyView());
  connect(_partyController, SIGNAL(operationOutcomeEvent(bool,string)),
          _view,            SLOT(manageOperationOutcome(bool,string)));

  _boxController = new PkmnBoxController(_model, _view->getBoxView());
  connect(_boxController, SIGNAL(operationOutcome(bool,string)),
          _view,          SLOT(manageOperationOutcome(bool,string)));

  _pokedexController = new PkmnPokedexController(_model, _view->getPokedexView());
  connect(_pokedexController, SIGNAL(operationOutcomeEvent(bool,string)),
          _view,              SLOT(manageOperationOutcome(bool,string)));

  // CONNECTION BETWEEN TOTALCONTROLLER & TOTALVIEW
  connect(_view, SIGNAL(saveToFileEvent()),
          this,  SLOT(manageSaveToFile()));
  connect(this,  SIGNAL(operationOutcomeEvent(bool,string)),
          _view, SLOT(manageOperationOutcome(bool,string)));


  createActions();
  _view -> manageOperationOutcome(true, "Application started.");

}

void PkmnSaveStateController::manageSaveToFile() {

  bool outcome;
  // PERFORMS INTEGRITY CHECK
  outcome = _model -> saveToFile();

  if (outcome)
    emit operationOutcomeEvent(true,
                               "Changes written to file.");
  else
    emit operationOutcomeEvent(false,
                               "Some error while saving changes to file.");

}

void PkmnSaveStateController::manageOpenFile() {

  QStringList fileNames = QFileDialog::getOpenFileNames(0, tr("Open File"),"./../",tr("PkmnYellow Save Files (*.sav)"));
  if (fileNames.size() == 0)
    return;
  if (fileNames.size() > 1) {
    emit operationOutcomeEvent(false,
                               "Cannot open more than a file at time.");
    return;
  }
  string filepath = fileNames[0].toStdString();

  bool outcome = _model->openFile(filepath);
  if (outcome)
    emit operationOutcomeEvent(true,
                               "Successfully opened the file.");
  else
    emit operationOutcomeEvent(false,
                               "Some error while opening the file.");

}

void PkmnSaveStateController::createActions() {

  QToolBar *toolBar = _view -> getMainToolBar();

  QAction *openFile = new QAction(QIcon::fromTheme("document-open"), "Open", this);
  connect(openFile, SIGNAL(triggered()), this, SLOT(manageOpenFile()));
  QAction *saveToFile = new QAction(QIcon::fromTheme("document-save"), "Save", this);
  connect(saveToFile, SIGNAL(triggered()), this, SLOT(manageSaveToFile()));

  QActionGroup *showGroup = new QActionGroup(this);
  QAction *showParty = new QAction(QIcon(":/img/pokeballSprite.png"), "Party Pokemon", showGroup);
  connect(showParty, SIGNAL(toggled(bool)), _view->getPartyView(), SLOT(setVisible(bool)));
  showParty->setCheckable(true);
  QAction *showBox = new QAction(QIcon(":/img/pokeballSprite.png"), "Box Pokemon", showGroup);
  connect(showBox, SIGNAL(toggled(bool)), _view->getBoxView(), SLOT(setVisible(bool)));
  showBox->setCheckable(true);
  QAction *showPokedex = new QAction(QIcon(":/img/pokeballSprite.png"), "Pokedex", showGroup);
  connect(showPokedex, SIGNAL(toggled(bool)), _view->getPokedexView(), SLOT(setVisible(bool)));
  showPokedex->setCheckable(true);

  QAction *enableCoherency = new QAction(QIcon::fromTheme("insert-link"), "Enable Game Coherency", this);
  connect(enableCoherency, SIGNAL(toggled(bool)), _partyController, SLOT(manageEnableCoherency(bool)));
  enableCoherency->setCheckable(true);
  enableCoherency->setChecked(true);

  toolBar -> addAction(openFile);
  toolBar -> addAction(saveToFile);
  toolBar -> addSeparator();
  toolBar -> addAction(showParty);
  toolBar -> addAction(showBox);
  toolBar -> addAction(showPokedex);
  toolBar -> addSeparator();
  toolBar -> addAction(enableCoherency);

}
