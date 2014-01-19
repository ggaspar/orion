#include <string>
#include <vector>
#include "resources.h"
#include "card.h"
#include "PlayerHuman.h"
#include "PlayerDerp.h"
#include "MatchState.h"
#include <map> 
#include "gameObjectManager.h"

//lame attempt to define a foreach.. to be reviewed later
//define foreachPlayer(index) for(index=0 ; index != _players.size(); ++index);


#ifndef __TABEL_H__
#define __TABEL_H__

using namespace std;



class GameBoard
{


	friend class Rules;
	
 public :
	GameBoard() : _matchState(0), isFirstRound(true)
	{
		_cards = new CardSet();
		_cards->createDeck();
		Player* player = new PlayerHuman("Human");
		PlayerId id = addPlayer(player, CardinalPosition::South);
		player = new PlayerDerp("Derp");
		id = addPlayer(player, CardinalPosition::North);
		_currentGamePhase = StartingRound;
	};

	enum GamePhase
	{
		StartingRound,
		Playing,
		NotPlaying,
		EndingRound,
		FinishingMatch
	};



	GamePhase go();
	void ShowStats();
	void processMatchWinner();



 private : 
	void playOneRound();


	Player* getCurrentPlayer();

	void UpdateMatchState();

	void defineFirstToPlay();

	void playCard();
	
	PlayerId addPlayer(Player* iPlayer, CardinalPosition pos);

	PlayerId getNextPlayer();	

	void newRound();

	void addCardToCurrentPlayer(Card* card);

	void addPoint();
	
	std::map<string,int> getScore() const;

	void dealCards();
	
	void endRound();

	MatchState getMatchState();

	void startNewMatch();

	int getNumberOfPlayers() const;

	PlayerStatus* getCurrentPlayerStatus();

	void cleanPlayedCards();


	map<PlayerId, Player*> _players;
	CardSet* _cards;
	map<PlayerId, PlayerStatus*> _allPlayersStatus;
	MatchState* _matchState;
	PlayerId _currentPlayer_id, _previousRoundWinner;
	bool isFirstRound;
	GameObjectManager* _gameObjectManager;
	GamePhase _currentGamePhase;


};

#endif