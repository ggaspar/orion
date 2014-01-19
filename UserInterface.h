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

	 static void showMatchScore(MatchState* matchState)
	 {
		cout << "Score Table:" << endl;

		map<PlayerId, PlayerStatus*>::iterator itPlayers = matchState->_allPlayersCurrentStatus->begin();

		while(itPlayers != matchState->_allPlayersCurrentStatus->end())
		{
			cout << itPlayers->second->_name << ": " << itPlayers->second->_points << endl;
			++itPlayers;
		}
	 }
	 static void showMatchWinner(const string iName)
	 {
		sf::Text text;
		sf::Vector2i pos = sf::Mouse::getPosition(Game::getWindow());

		std::stringstream ss;
		ss << iName << " wan this match!" ;
		//VisibleGameObject* object = _gameObjectManager.getClickedObject(pos);		
		string statusInfo = ss.str();			
		text.setString(statusInfo);
		text.setCharacterSize(24); // in pixels, not points!
		text.setColor(sf::Color::White);
		int centerWidth = WINDOW_WIDTH / 2;
		int centerHeight = WINDOW_HEIGHT / 2;

		sf::Font font;
		text.setPosition( centerWidth, centerHeight );
		// Load it from a file
		if (!font.loadFromFile("assets/sansation.ttf"))
	    //find this file in the "pong" example in the SFML examples folder
		{
		    std::cout << "Error loading font\n" ;
		}
		text.setFont(font);
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		//text.setPosition(50,500);
		Game::getWindow().draw(text);
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

	static Card* getCardToPlay()
	{
		VisibleGameObject* card = 0;
		if(Game::_currentEvent.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i position = sf::Mouse::getPosition(Game::getWindow());		
			card = Game::_gameObjectManager.getClickedObject(position);
		}
		Card* card2 = dynamic_cast<Card*>(card);
		return card2;
	}


	static void showPlayerCards(const CardSet& iCards)
	{
		for ( int i = 0; i != iCards.size(); ++i)
		{
			cout << i+1 << ": " << iCards.chooseCard(i) << endl;
		}
	}

	static void showMatchState(PlayerStatus playerStatus)
	{

		sf::Text text;
		sf::Vector2i pos = sf::Mouse::getPosition(Game::getWindow());

		std::stringstream ss;
		ss << playerStatus._name << ": " << playerStatus._points << " points!" ;
		//VisibleGameObject* object = _gameObjectManager.getClickedObject(pos);		
		string statusInfo = ss.str();			
		text.setString(statusInfo);
		text.setCharacterSize(16); // in pixels, not points!
		text.setColor(sf::Color::Blue);
		int center = WINDOW_WIDTH / 2;

		switch (playerStatus._position)
		{
			case CardinalPosition::North :
				text.setPosition( center, N_STATUS_POSITION_Y );
				break;
			case CardinalPosition::South :
				text.setPosition( center, S_STATUS_POSITION_Y );
				break;
			default:
				break;
		}
		sf::Font font;
	
		// Load it from a file
		if (!font.loadFromFile("assets/sansation.ttf"))
	    //find this file in the "pong" example in the SFML examples folder
		{
		    std::cout << "Error loading font\n" ;
		}
		text.setFont(font);
		if(playerStatus._isFirst)
		{
			text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		}
		//text.setPosition(50,500);
		Game::getWindow().draw(text);
	}
};

#endif
