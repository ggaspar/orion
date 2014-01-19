#include <iostream>
#include <string>
#include "visibleGameObject.h"
#include "tools.h"


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
	
	CardSuit(char cSuit) : _cSuit(cSuit){};
	
	
	bool operator==(const CardSuit& otherCs) const
	{
		return otherCs._cSuit==_cSuit;
	};
  
	friend ostream& operator<<(ostream &out, const CardSuit& c)
	{
		cout <<  c._cSuit;
		return out;	
	}

	char _cSuit;

};


class Card :
	public VisibleGameObject
{
	
 public :
	Card() : _rank(0) {};
	//int  _width, _height;


	Card(char face, char suit, int rank) ;

	//TODO: review this copy constructor
	Card(const Card& c);

	friend ostream& operator<<(ostream &out, const Card& c)
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

	string getSuitName();

	string getCardName();
  	CardFace _face;
	CardSuit _suit;
	sf::Vector2f _playedPosition;
	int _rank;
	float _velocity;
	bool _beingPlayed;

	void playCard();

	bool isCentered();

	void update(float elapsedTime);
	sf::Vector2f getPlayedPosition();
	void setPlayedPosition(sf::Vector2f iPlayedPosition);

};


#endif
