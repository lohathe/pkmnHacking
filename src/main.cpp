#include <QApplication>

#include "pkmnsavestate.h"
#include "pkmnsavestatemodel.h"
#include "pkmnsavestatecontroller.h"
#include "pkmnsavestateview.h"

#include "pkmnstringreader.h"
#include "pkmndataformat.h"
#include <iostream>
using namespace std;
#include "pkmnspeciesdescriptor.h"
#include "pkmnspecies.h"
#include "pkmncomputevaluesutility.h"

int main (int argc, char **argv) {
/*
  byte *name = PkmnStringReader::fromStdString("KUBLA");
  for (int i=0; i<11; ++i) {
    cout<<hex<<(static_cast<int>(name[i])&0xFF)<<" ";
  }
  cout<<endl;
  return 0;
*/

/*
  const PkmnSpeciesDescriptor *d = PkmnSpeciesDescriptorList::get(PkmnSpeciesList::getByName("Nidorino")->getIndex());
  cout<<PkmnSpeciesList::getByIndex(d->getIndex())->getName()<<endl;
  for (int i=0; i<20; ++i) {
    cout<<"lvl "<<i<<") "<<PkmnComputeValuesUtility::computeExpForLevel(d, i)<<endl;
  }
*/

  QApplication app(argc, argv);

  //new PkmnSaveStateController("/home/luca/Desktop/Saves/prova/pmyellow151.sav");
  new PkmnSaveStateController("");
  return app.exec();

}
