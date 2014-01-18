#include "card.h"
#include "playerStatus.h"
#include <map>


#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

//TODO: enhance this class
class GameState
{
 friend class GameBoard;

 public :
  GameState(map<PlayerId, PlayerStatus*>* playersStatus) : _allPlayersCurrentStatus(0)
  {
	_allPlayersCurrentStatus = playersStatus;
  }

  GameState() : _allPlayersCurrentStatus(0){};

  CardSuit _masterSuit;
  map<PlayerId, PlayerStatus*>* _allPlayersCurrentStatus;

  bool isPlayerFirstToPlay(PlayerId player);

  bool hasPlayerPlayed(const PlayerId player);

  Card* getCardOfPlayer(PlayerId player);

 private :
	void defineFirstToPlay(PlayerId player);

	void playerPlays(PlayerId player);

	void newRound(PlayerId winner);

	void addCardToPlayer(PlayerId player, Card* card);

	void addPoint(PlayerId player);
};

#endif
