#include "rules.h"
#include "UserInterface.h"
#include "resources.h"
#include <map>



int Rules::isStateValid(MatchState& matchState, CardSet& cards, Card& playedCard)
{
	bool isNotValid = false;
	int result = VALID_MOVE;
	if (matchState.isFirstRound())
	{
		result = VALID_MOVE;		
	}
	else if(!rValidSuit(matchState._masterSuit, cards, playedCard))
	{
		result = SUIT_NOT_FOLLOWING_MASTER;
	}
	return result;
}

bool Rules::rValidSuit(CardSuit& masterCardSuit, CardSet& cards, Card& playedCard)
{
	return masterCardSuit==NULL ||  masterCardSuit==playedCard._suit || !cards.hasSuit(masterCardSuit); 
}


//two bellow methods could be one template method
//bug: doesn't recognize draws
//quick solution, only working with 2 players
//#define PLAYER1 0
//#define PLAYER2 1
#define CARD playersIt->second->_card
//#define CARD2 (*gameBoard->_players[PLAYER2]->_card)

PlayerId Rules::getRoundWinner(MatchState& matchState)
{		
	map<PlayerId, PlayerStatus*>::const_iterator playersIt;
	Card* currentHighestCard = new Card();
	PlayerId currentWinner = -1;
	
	for(playersIt = matchState._allPlayersCurrentStatus->begin();
		playersIt != matchState._allPlayersCurrentStatus->end();
		++playersIt)
	{
		if(currentHighestCard == 0)
		{
			currentHighestCard = CARD;
			currentWinner = playersIt->first;
			continue;
		}
		if( matchState._masterSuit == CARD->_suit._cSuit &&
			(*currentHighestCard) < (*CARD) )
		{
			currentHighestCard = CARD;
			currentWinner = playersIt->first;
			continue;
		}
		
	}
	
	return currentWinner;
	/*
	if(CARD1._suit._cSuit!=tabel->_masterSuit._cSuit)
	{
	    return PLAYER2;
	}
	if(CARD2._suit._cSuit!=tabel->_masterSuit._cSuit)
	{
	    return PLAYER1;
	}
	if( CARD1 > CARD2 )
	{
		return PLAYER1;
	}
	else 
	{
		return PLAYER2;
	}*/
/*
	Card* highestCard = tabel->_players[0]->_card;
	PlayerId highestPlayerId=0;


	for(int pIndex = 0;	pIndex < tabel->_players.size(); ++pIndex)
	{
			
		if((*highestCard) < (*tabel->_players[pIndex]->_card))
		{
			highestPlayerId = tabel->_players[pIndex]->_playerId;
			highestCard = tabel->_players[pIndex]->_card;
		}
	}
	return highestPlayerId;*/
}

PlayerId Rules::getMatchWinner(MatchState& matchState)
{
	int topPoints = 0;
	PlayerId highestPlayerId = -1;
	for(int pIndex = 0;	pIndex < matchState._allPlayersCurrentStatus->size(); ++pIndex)
	{
		if(topPoints < (*matchState._allPlayersCurrentStatus)[pIndex]->_points)
		{
			highestPlayerId = (*matchState._allPlayersCurrentStatus)[pIndex]->_playerId;
			topPoints = (*matchState._allPlayersCurrentStatus)[pIndex]->_points;
		}
	}
	return highestPlayerId;
}

int Rules::roundsToPlay(MatchState& matchState)
{
	return matchState._allPlayersCurrentStatus->begin()->second->_cardsLeft;

}

int Rules::NumberOfInitialCards()
{
	return 5;
}

CardSet* Rules::getLegalCards(MatchState& iMatchState, const CardSet& iCardSet)
{
	if (iMatchState.isFirstRound())
	{
		return (CardSet*)&iCardSet;
	}
	CardSet* legalCardSet = iCardSet.getCardsBySuit(iMatchState._masterSuit);
	//cout << "legal cards: " << endl;
	//UserInterface::showPlayerCards(*legalCardSet);
	if(legalCardSet->size() == 0)
		return (CardSet*)&iCardSet;
	else
		return legalCardSet;
}


