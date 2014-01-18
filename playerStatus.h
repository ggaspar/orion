#include "resources.h"
#include "card.h"

#ifndef __PLAYER_STATUS_H__
#define __PLAYER_STATUS_H__

class PlayerStatus
{	
 public :
	PlayerStatus(PlayerId id, string name, int initialNumberOfCards) : _points(0), _played(false), 
								_isFirst(false), _card(NULL),
								_playerId(id), _name(name), _cardsLeft(initialNumberOfCards) {};
	bool _played;
	string _name;
	bool _isFirst;
	Card *_card;
	int _cardsLeft;
	PlayerId _playerId;
	int _points;
};

#endif