#include "matchState.h"

bool MatchState::isPlayerFirstToPlay(PlayerId player)
{
	return (*_allPlayersCurrentStatus)[player]->_isFirst;
}
bool MatchState::hasPlayerPlayed(const PlayerId player)
{
	return (*_allPlayersCurrentStatus)[player]->_played;
}

Card* MatchState::getCardOfPlayer(PlayerId player)
{
	return (*_allPlayersCurrentStatus)[player]->_card;
}

void MatchState::defineFirstToPlay(PlayerId player)
{
	(*_allPlayersCurrentStatus)[player]->_isFirst=true;
}

void MatchState::playerPlays(PlayerId player)
{
	(*_allPlayersCurrentStatus)[player]->_played=true;
	(*_allPlayersCurrentStatus)[player]->_cardsLeft--;
}
void MatchState::newRound(PlayerId winner)
{
	for(int pIndex = 0;	pIndex < (*_allPlayersCurrentStatus).size(); ++pIndex)
	{ 
		(*_allPlayersCurrentStatus)[pIndex]->_played=false;		
		(*_allPlayersCurrentStatus)[pIndex]->_isFirst = (winner==(*_allPlayersCurrentStatus)[pIndex]->_playerId);
	}	
	++_roundNumber;
}

void MatchState::addCardToPlayer(PlayerId player, Card* card)
{
	if(isPlayerFirstToPlay(player))
	{
		_masterSuit = card->_suit;
	}
	(*_allPlayersCurrentStatus)[player]->_card=card;
}

void MatchState::addPoint(PlayerId player)
{
	(*_allPlayersCurrentStatus)[player]->_points++;
}

bool MatchState::isFirstRound()
{
	for(int pIndex = 0;	pIndex < (*_allPlayersCurrentStatus).size(); ++pIndex)
	{ 
		if((*_allPlayersCurrentStatus)[pIndex]->_played)
		{
			return false;
		}
	}
	return true;
}
