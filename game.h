
#include "stdsfml.h"
#include "gameObjectManager.h"
#include "gameBoard.h"

#ifndef __GAME_H__
#define __GAME_H__



class Game
{

	enum GameState
	{
		Uninitialized,
		ShowingSplash,
		Paused,
		ShowingMenu,
		Playing,
		Exiting
	};

 public :
	 
	 //Game() : _gameBoard(0), _gameState(Uninitialized)
		 
	//{
		//createGameBoard();
		//createPlayers();
	



	//static void createGameBoard();
	
	//static void announceWinner();

	static void startGame();
	static sf::Event _currentEvent;
	static sf::RenderWindow& Game::getWindow();
	static GameObjectManager _gameObjectManager;

 private :	
	static map<PlayerId,string> _players;
	
	static GameState _gameState;		
	//static CardSet* _cards;
	//static Rules* _rules;
	static GameBoard* _gameBoard;
	static sf::RenderWindow _mainWindow;
	static sf::Clock _clock;
	static GameBoard::GamePhase _matchPhase;
	static float _waitingTime;

	
	
	static bool isExiting();
	static void createPlayers();
	static void gameLoop();
	static void showSplashScreen();
	static void showMenu();
	static void plays();
	static void showDebug();
	
 
};
#endif