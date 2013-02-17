#include "pkmnstringreader.h"

string PkmnStringReader::toStdString(const byte *name) {
  string result = "";
  
  for (int i=0; i<11; ++i) {
    int readChar = static_cast<int>(name[i]) & 0xFF;
    if (readChar == 0x50) 
      break;
    else if (readChar >= 0x80 && readChar <= 0x99)
      result.push_back('A' + readChar - 0x80);
    else if (readChar >= 0xA0 && readChar <= 0xB9)
      result.push_back('a' + readChar - 0xA0);
    else if (readChar >= 0xF6 && readChar <= 0xFF)
      result.push_back('0' + readChar - 0xF6);
    else if (readChar == 0xAE)
      result.push_back('M');
    else if (readChar == 0xF5)
      result.push_back('F');
/*    else if (readChar == 0xAE)
      result.push_back(0x0B);
    else if (readChar == 0xF5)
      result.push_back(0x0C);*/
    else
      result.push_back('.');
  }
  
  return result;
}

byte* PkmnStringReader::fromStdString(const string &name) {

  byte* result = new byte[11];
  
  int max = std::min(11, static_cast<int>(name.size()));
  for (int i=0; i<max; ++i) {
    int readChar = name[i];
    if (readChar >= 'a' && readChar <= 'z')
      result[i] = static_cast<byte>( 0xA0 + readChar - 'a' );
    else if (readChar >= 'A' && readChar <= 'Z')
      result[i] = static_cast<byte>( 0x80 + readChar - 'A' );
    else
      result[i] = static_cast<byte>( 0xE6 );
  }
  for (int i=max; i<11; ++i) {
    result[i] = static_cast<byte>( 0x50 );
  }

  return result;
}
