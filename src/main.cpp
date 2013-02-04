#include <QApplication>

#include "pkmnsavestate.h"
#include "pkmnsavestatemodel.h"
#include "pkmnsavestatecontroller.h"
#include "pkmnsavestateview.h"

int main (int argc, char **argv) {

  QApplication app(argc, argv);

  new PkmnSaveStateController("/home/luca/Desktop/Saves/prova/pmyellow.sav");
  //PkmnSaveStateView *a =new PkmnSaveStateView();

  return app.exec();

}
