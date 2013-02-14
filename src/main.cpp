#include <QApplication>

#include "pkmnsavestate.h"
#include "pkmnsavestatemodel.h"
#include "pkmnsavestatecontroller.h"
#include "pkmnsavestateview.h"

#include "pkmnstringreader.h"
#include "pkmndataformat.h"
#include <iostream>
using namespace std;

int main (int argc, char **argv) {
/*
  byte *name = PkmnStringReader::fromStdString("KUBLA");
  for (int i=0; i<11; ++i) {
    cout<<hex<<(static_cast<int>(name[i])&0xFF)<<" ";
  }
  cout<<endl;
  return 0;
*/
  QApplication app(argc, argv);

  new PkmnSaveStateController("/home/luca/Desktop/Saves/prova/pmyellow.sav");

  return app.exec();

}
