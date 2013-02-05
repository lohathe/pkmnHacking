#ifndef PKMN_MOVE
#define PKMN_MOVE

#include "pkmnelement.h"
#include "pkmntype.h"

#include <string>
using std::string;
#include <vector>
using std::vector;

class PkmnMove {

public:

  PkmnMove (int, const string &, byte, byte, int, int, int);

  int getId () const;
  string getName () const;
  byte getElement () const;
  byte getType () const;
  int getPP () const;
  int getPwr () const;
  int getAcc () const;

private:

  int _id;
  string _name;
  byte _element;
  byte _type;
  int _pp, _power, _accuracy;

};

class PkmnMoveList {

public:
  
  static const PkmnMove * get (int);
  static const PkmnMove * get (const string &);
  static vector<const PkmnMove *> getWholeList();
  static vector<const PkmnMove *> getByElement(byte);
  static vector<const PkmnMove *> getByType(byte);

private:

  static const PkmnMove _movesList[166];

};

#endif // PKMN_MOVE
