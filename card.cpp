#include <iostream>
#include <string>
#include "resources.h"

#ifndef __CARD_H__
#define __CARD_H__

using namespace std;

class CardFace
{
 public :
  CardFace() : _cFace('\0'){};
  CardFace(char cFace) : _cFace(cFace){};
  char _cFace;
  bool operator==(const CardFace& otherCf) const
  {
   return otherCf._cFace==_cFace;
  };
};

class CardSuit
{
 public :
	 CardSuit() : _cSuit('\0'){};
  CardSuit(char cSuit) : _cSuit(cSuit) {};
  char _cSuit;
  bool operator==(const CardSuit& otherCs) const
  {
   return otherCs._cSuit==_cSuit;
  };
  
  friend ostream& operator<<(ostream &out, const CardSuit& c)
  {
   cout <<  c._cSuit;
   return out;

  }

};

  
  CardFace _face;
  CardSuit _suit;
  int _rank;

  friend ostream& Card::operator<<(ostream &out, const Card& c)
  {
	  out << c._face._cFace << " " << c._suit._cSuit;
   return out;
  };
  friend bool operator>(const Card& c1, const Card& c2)
  {
    return c1._rank > c2._rank;
  };
  friend bool operator<(const Card& c1, const Card& c2)
  {
    return c1._rank < c2._rank;
  };
  bool operator==(const Card& otherC) const
  {
   return otherC._face==_face && otherC._suit==_suit;
  };

};


#endif
