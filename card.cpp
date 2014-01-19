#include <iostream>
#include <string>
#include "visibleGameObject.h"
#include "tools.h"
#include "card.h"

using namespace std;

Card::Card(char face, char suit, int rank) : _face(face), _suit(suit), _rank(rank), _beingPlayed(false), _velocity(-1)//,_width(75), _height(107)
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
Card::Card(const Card& c) : _face(c._face), _suit(c._suit), _rank(c._rank), _beingPlayed(false), _velocity(-1)//,  _width(75), _height(107)
{
	std::stringstream cardName;
	cardName << "assets/images/cards/" << getSuitName() << "-" << _face._cFace << "-75.png";
	string strCardName = cardName.str();
	load(strCardName);
	//assert(isLoaded());
	VisibleGameObject::_width = 75;
	VisibleGameObject::_height = 107;
};

string Card::getSuitName()
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


string Card::getCardName()
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

void Card::playCard()
{
	cout << "card is going to be played" << endl;
	_beingPlayed = true;
}
	

bool Card::isCentered()
{
	sf::Vector2f pos = getPosition();

	if(pos.y < (600/2) - 45)
		return true;
	return false;
}

void Card::update(float elapsedTime)
{
	sf::Vector2f pos = this->getPosition();
		
	if(_beingPlayed)// && !isCentered())
	{
		//getSprite().move(0, _velocity * elapsedTime );
		this->setPosition(_playedPosition.x, _playedPosition.y);
	}
}

void Card::setPlayedPosition(sf::Vector2f iPlayedPosition)
{
	_playedPosition = iPlayedPosition;
}

sf::Vector2f Card::getPlayedPosition()
{
	return _playedPosition;
}


