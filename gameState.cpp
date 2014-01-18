#include "gameState.h"

bool GameState::isPlayerFirstToPlay(PlayerId player)
{
	return (*_allPlayersCurrentStatus)[player]->_isFirst;
}
bool GameState::hasPlayerPlayed(const PlayerId player)
{
	return (*_allPlayersCurrentStatus)[player]->_played;
}

Card* GameState::getCardOfPlayer(PlayerId player)
{
	return (*_allPlayersCurrentStatus)[player]->_card;
}

void GameState::defineFirstToPlay(PlayerId player)
{
	(*_allPlayersCurrentStatus)[player]->_isFirst=true;
}

void GameState::playerPlays(PlayerId player)
{
	(*_allPlayersCurrentStatus)[player]->_played=true;
	(*_allPlayersCurrentStatus)[player]->_cardsLeft--;
}
void GameState::newRound(PlayerId winner)
{
	for(int pIndex = 0;	pIndex < (*_allPlayersCurrentStatus).size(); ++pIndex)
	{ 
		(*_allPlayersCurrentStatus)[pIndex]->_played=false;		
		(*_allPlayersCurrentStatus)[pIndex]->_isFirst = (winner==(*_allPlayersCurrentStatus)[pIndex]->_playerId);
	}
}

void GameState::addCardToPlayer(PlayerId player, Card* card)
{
	if(isPlayerFirstToPlay(player))
	{
		_masterSuit = card->_suit;
	}
	(*_allPlayersCurrentStatus)[player]->_card=card;
}

void GameState::addPoint(PlayerId player)
{
	(*_allPlayersCurrentStatus)[player]->_points++;
}
