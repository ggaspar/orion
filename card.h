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


	Card(char face, char suit, int rank) : _face(face), _suit(suit), _rank(rank), _beingPlayed(false), _velocity(-1)//,_width(75), _height(107)
	{
		std::stringstream ss;
		ss << "assets/images/cards/" << getSuitName() << "-" << _face._cFace << "-75.png";
		string cardName = ss.str();
		load(cardName);
		//assert(isLoaded());
		VisibleGameObject::_width = 75;
		VisibleGameObject::_height = 107;
	};

	//TODO: review this copy constructor
	Card(const Card& c) : _face(c._face), _suit(c._suit), _rank(c._rank), _beingPlayed(false), _velocity(-1)//,  _width(75), _height(107)
	{
		std::stringstream cardName;
		cardName << "assets/images/cards/" << getSuitName() << "-" << _face._cFace << "-75.png";
		string strCardName = cardName.str();
		load(strCardName);
		//assert(isLoaded());
		VisibleGameObject::_width = 75;
		VisibleGameObject::_height = 107;
	};

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

	string getSuitName()
	{
		if(_suit._cSuit == 'D')
			return "diamonds";
		if(_suit._cSuit == 'C')
			return "clubs";
		if(_suit._cSuit == 'S')
			return "spades";
		else //		if(_suit._cSuit == 'D')
			return "hearts";
	};


	string getCardName()
	{
		std::stringstream cardName;
		cardName << _face._cFace << _suit._cSuit;
		return cardName.str();			
	}
  	CardFace _face;
	CardSuit _suit;
	int _rank;
	float _velocity;
	bool _beingPlayed;

	void playCard()
	{
		cout << "card is going to be played" << endl;
		_beingPlayed = true;
	}
	

	bool isCentered()
	{
		sf::Vector2f pos = getPosition();

		if(pos.y < (600/2) - 45)
			return true;
		return false;
	}

	void update(float elapsedTime)
	{
		sf::Vector2f pos = this->getPosition();
		
		if(_beingPlayed && !isCentered())
		{
			//getSprite().move(0, _velocity * elapsedTime );
			this->setPosition(400, 255);
		}
	}
};


#endif
