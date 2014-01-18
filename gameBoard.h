#include <string>
#include <vector>
#include "resources.h"
#include "card.h"
#include "PlayerHuman.h"
#include "PlayerDerp.h"
#include "GameState.h"
#include <map> 
#include "gameObjectManager.h"

//lame attempt to define a foreach.. to be reviewed later
//define foreachPlayer(index) for(index=0 ; index != _players.size(); ++index);


#ifndef __TABEL_H__
#define __TABEL_H__

using namespace std;



class GameBoard
{

	enum GamePhase
	{
		StartingRound,
		Playing
	};

	friend class Rules;
	
 public :
	GameBoard() : _gameState(0), isFirstRound(true)
	{
		_cards = new CardSet();
		_cards->createDeck();
		Player* player = new PlayerHuman("Human");
		PlayerId id = addPlayer(player);
		player = new PlayerDerp("Derp");
		id = addPlayer(player);
		_currentGamePhase = StartingRound;
	};


	void go();

 private : 
	void playOneRound();

	void announceWinner();

	Player* getCurrentPlayer();

	void UpdateGameState();

	void defineFirstToPlay();

	void playCard();
	
	PlayerId addPlayer(Player* iPlayer);

	PlayerId getNextPlayer();	

	void newRound(PlayerId winner);

	void addCardToCurrentPlayer(Card* card);

	void addPoint(PlayerId id);
	
	std::map<string,int> getScore() const;

	void dealCards();
	
	void endRound();

	GameState getGameState();

	void startGame();

	int getNumberOfPlayers() const;

	PlayerStatus* getCurrentPlayerStatus();



	map<PlayerId, Player*> _players;
	CardSet* _cards;
	map<PlayerId, PlayerStatus*> _allPlayersStatus;
	GameState* _gameState;
	PlayerId _currentPlayer_id, _previousRoundWinner;
	bool isFirstRound;
	GameObjectManager* _gameObjectManager;
	GamePhase _currentGamePhase;

};

#endif