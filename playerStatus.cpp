#include "playerStatus.h"
	
void PlayerStatus::reset(int initialNumberOfCards)
{
	_played=false;
	_isFirst=false;
	_card=0;
	_cardsLeft = initialNumberOfCards;
	_points=0;

}
