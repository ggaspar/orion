#include "player.h"

#ifndef __PLAYER_HUMAN_H__
#define __PLAYER_HUMAN_H__
using namespace std;

class PlayerHuman : public Player
{
 public:
	PlayerHuman(string name) : Player(name) {};
	Card* playCard(int invalidErrorMessage);

	void organizeCards();

	sf::Vector2f getPlayedCardPosition();


};

#endif
