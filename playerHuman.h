#include "player.h"

#ifndef __PLAYER_HUMAN_H__
#define __PLAYER_HUMAN_H__
using namespace std;

class PlayerHuman : public Player
{
 public:
  PlayerHuman(string name) : Player(name) {};
  Card* playCard(int invalidErrorMessage);

  void organizeCards()
  {
	  float pos = 800/4 - 80;
	  for (int i = 0; i < getCards().size(); i++, pos= pos + 80)
	  {
		  Card* card = getCard(i);		  
		  card->setPosition(pos, 480.0);
		  card->activate();
	  }
  };


};

#endif
