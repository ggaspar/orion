#include "playerStatus.h"
#include "rules.h"
#include "resources.h"
#include "tools.h"
#include "Game.h"
#include <map>

#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__


class UserInterface
{
 public :
	 static void showCardPlayed(const string iPlayerName, const Card& iCard)
	 {
		cout << "player " << iPlayerName  << " plays " << iCard;
		cout << endl;

	 }
	 static void showRoundWinner(const string iPlayerName)
	 {
		cout << "player "<< iPlayerName <<" wins this round." << endl;
	 }

	 static void showMatchScore(GameState* gameState)
	 {
		cout << "Score Table:" << endl;

		map<PlayerId, PlayerStatus*>::iterator itPlayers = gameState->_allPlayersCurrentStatus->begin();

		while(itPlayers != gameState->_allPlayersCurrentStatus->end())
		{
			cout << itPlayers->second->_name << ": " << itPlayers->second->_points << endl;
			++itPlayers;
		}
	 }
	 static void showMatchWinner(const string iName)
	 {
		cout << "Player " << iName << " WON the GAME!!!" << endl;
	 }

	 static void showMatchDraw()
	 {
	 	cout << "It was a draw!" << endl;
	 }

	static void showInvalidMoveMessage(int invalidErrorMessage, string extraInfo = "")
	{
		switch (invalidErrorMessage)
		{
			case SUIT_NOT_FOLLOWING_MASTER : 
				cout << "Invalid move! You must follow the suit played!" << endl;
				break;
			case CARD_NOT_RECOGNIZED : 
				cout << "Card/Command not recognized. Please type a number between 1 and " << extraInfo << endl;
				break;

			default:
				break;
		}
	}

	static int getCardToPlayConsole()
	{
		string sPlay;
		cout << "which card you want to play?" << endl;
		cin >> sPlay;

		int iPlay = StringToNumber<int>(sPlay);

		return iPlay;
	}

	static VisibleGameObject* getCardToPlay()
	{
		VisibleGameObject* card = 0;
		if(Game::_currentEvent.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i position = sf::Mouse::getPosition(Game::getWindow());		
			VisibleGameObject* card = Game::_gameObjectManager.getClickedObject(position);
		}
		return card;
	}


	static void showPlayerCards(const CardSet& iCards)
	{
		for ( int i = 0; i != iCards.size(); ++i)
		{
			cout << i+1 << ": " << iCards.chooseCard(i) << endl;
		}
	}
};

#endif
