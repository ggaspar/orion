#include "matchState.h"
#include "cardSet.h"


#ifndef __RULES_H__
#define __RULES_H__


class Rules
{
  public :
	Rules(){};

	static int isStateValid(MatchState& matchState, CardSet& cards, Card& playedCard);

	static PlayerId getRoundWinner(MatchState& matchState);

	static PlayerId getMatchWinner(MatchState& matchState);

	static CardSet* getLegalCards(MatchState& matchState, const CardSet& iCardSet);

	static bool rValidSuit(CardSuit& masterCardSuit, CardSet& cards, Card& playedCard);
	
	static int roundsToPlay(MatchState& matchState);
	
	static int NumberOfInitialCards();

};
#endif


