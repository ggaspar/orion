#include "card.h"
#include "playerStatus.h"
#include <map>


#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

//TODO: enhance this class
class MatchState
{
 friend class GameBoard;

 public :
  MatchState(map<PlayerId, PlayerStatus*>* playersStatus) : _allPlayersCurrentStatus(0), _roundNumber(1)
  {
	_allPlayersCurrentStatus = playersStatus;
  }

  MatchState() : _allPlayersCurrentStatus(0){};

  CardSuit _masterSuit;

  int _roundNumber;
  map<PlayerId, PlayerStatus*>* _allPlayersCurrentStatus;

  bool isPlayerFirstToPlay(PlayerId player);

  bool hasPlayerPlayed(const PlayerId player);

  Card* getCardOfPlayer(PlayerId player);

  bool isFirstRound();

 private :
	void defineFirstToPlay(PlayerId player);

	void playerPlays(PlayerId player);

	void newRound(PlayerId winner);

	void addCardToPlayer(PlayerId player, Card* card);

	void addPoint(PlayerId player);
};

#endif
