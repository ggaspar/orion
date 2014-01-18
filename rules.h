#include "gameState.h"
#include "cardSet.h"


#ifndef __RULES_H__
#define __RULES_H__


class Rules
{
  public :
	Rules(){};

	static int isStateValid(GameState& gameState, CardSet& cards, Card& playedCard);

	static PlayerId getRoundWinner(GameState& gameState);

	static PlayerId getGameWinner(GameState& gameState);

	static CardSet* getLegalCards(GameState& gameState, const CardSet& iCardSet);

	static bool rValidSuit(CardSuit& masterCardSuit, CardSet& cards, Card& playedCard);
	
	static int roundsToPlay(GameState& gameState);
	
	static int NumberOfInitialCards();

};
#endif


