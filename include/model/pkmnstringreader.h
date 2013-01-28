#ifndef PKMN_STRING_READER
#define PKMN_STRING_READER

#include "pkmndataformat.h"

#include <string>
using std::string;

class PkmnStringReader {
public:

  static string toStdString(const byte *name);
  static byte* fromStdString(const string &name);

};

#endif // PKMN_STRING_READER

/* 
    Character 50 terminates a string.
    Characters 60-6F are bold ABCDEFGHIVSLM, colon, and katakana small I and U. (I think)
    Characters 70-75 are both single quotes, both double quotes, floating dot, and floating ellipis.
    Characters 76-7E are small hiragana A, E and O, and five menu border characters.
    Character 7F is space.
    Characters 80-99 are uppercase A through Z.
    Characters 9A-9F are ():;[].
    Characters A0-B9 are lowercase a through z.
    Characters BA-BF are é, 'd, 'l, 's, 't, and 'v.
    Characters C0-DF appear to be blank.
    Characters E1-E9 are PK, MN, -, 'r, 'm, ?, !, ., and small katakana A.
    Characters EA-EF are small katakana U, small katakana I, white right facing triangle, black right facing triangle, black down facing triangle, and the male symbol.
    Characters F0-F5 are the Pokédollar logo, multiplication cross, full stop, slash, comma, and female symbol.
    Characters F6-FF are the digits 0 through 9.
    Other characters seem to do weird things. 

0x307e => inizio nomi pokemon

0x2f2c => numero pokemon in lista
0x2f2d => lista della specie dei pokemon in lista
0x2f33 => 0xFF
0x2f34 => info primo pokemon ...

*/

