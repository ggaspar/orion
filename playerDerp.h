#include "player.h"

#ifndef __PLAYER_DERP_H__
#define __PLAYER_DERP_H__

class PlayerDerp  : public Player
{
 public:
    PlayerDerp(string name) : Player(name) {};

	Card* playCard(int invalidErrorMessage);
	void organizeCards();
	
	sf::Vector2f getPlayedCardPosition();


};

#endif
