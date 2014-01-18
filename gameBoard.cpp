#include <string>
#include <vector>
#include "gameBoard.h"
#include "rules.h"
#include <map>
#include "resources.h"
#include "UserInterface.h"
#include "tools.h"
#include "Game.h"
#include <algorithm>


void GameBoard::go()
{
	switch (_currentGamePhase)
	{
		case GameBoard::StartingRound:
			startGame();
			break;
		case GameBoard::Playing:
			playOneRound();
			break;
		default:
			break;
	}
}


PlayerId GameBoard::addPlayer(Player* iPlayer)
{
	PlayerId id = _allPlayersStatus.empty() ? 0 : _players.size();
	_allPlayersStatus[id] = (new PlayerStatus(id, iPlayer->getName(),  Rules::NumberOfInitialCards()));
	_players[id] = iPlayer;
	return id;
}


void GameBoard::startGame()
{
	_gameState = new GameState(&_allPlayersStatus);
	dealCards();
	defineFirstToPlay();
	//TODO: erase allPlayersStatus
	/*while (Rules::roundsToPlay(*_gameState)>0)
	{
		
		playOneRound();
		isFirstRound=false;
	}
	announceWinner();*/
}

void GameBoard::announceWinner()
{
	PlayerId winner = Rules::getGameWinner(*_gameState);
	if(winner == -1)
	{
		UserInterface::showMatchDraw();
	}
	else
	{
		UserInterface::showMatchWinner(_players[winner]->_name);
	}	
}

void GameBoard::playOneRound()
{			
	//do
	//{
		playCard();		
	//}
	//while( getNextPlayer() != -1);			
	//endRound();
}

void GameBoard::dealCards()
{
	_cards->shuffle();
	for (int i = 0; i <  Rules::NumberOfInitialCards() ; ++i)
	{
		map<PlayerId, Player*>::iterator playersIt = _players.begin();
		for( ; playersIt != _players.end(); ++playersIt)
		{
			Card* card = _cards->popCard();
			(*playersIt).second->receiveCard(card);
		}
	}

	map<PlayerId, Player*>::iterator playersIt = _players.begin();
	for( ; playersIt != _players.end(); ++playersIt)
	{
		//Card* card = _cards->popCard();
		(*playersIt).second->organizeCards();;
	}
	_currentGamePhase = Playing;
}

int GameBoard::getNumberOfPlayers() const
{
	return _gameState->_allPlayersCurrentStatus->size();
}

void GameBoard::defineFirstToPlay()
{
	//to randomly choose a player, if there's no defined first player
	/*int i = randomInt(_players.size());
	
	//TODO: iterate over playerIds (first of map players)
	for(int pIndex = 0;	pIndex < getNumberOfPlayers(); ++pIndex)
	{ 
		if (_gameState->isPlayerFirstToPlay(pIndex))
		{
			i = pIndex;
		}
	}
	_gameState->defineFirstToPlay(i);
	_currentPlayer_id = i;*/
	_currentPlayer_id = 0;
}

PlayerStatus* GameBoard::getCurrentPlayerStatus()
{
	return (*_gameState->_allPlayersCurrentStatus)[_currentPlayer_id];
}

Player* GameBoard::getCurrentPlayer()
{
	return _players[_currentPlayer_id];
}

PlayerId GameBoard::getNextPlayer()
{
	_gameState->playerPlays(_currentPlayer_id);
	++_currentPlayer_id;
	//TODO: add list of IDs
	if(getNumberOfPlayers() <= _currentPlayer_id)
	{
		_currentPlayer_id=0;
	}
	if(_gameState->hasPlayerPlayed(_currentPlayer_id))
	{
		_currentPlayer_id = -1;
	}
	return _currentPlayer_id;	
}

void GameBoard::newRound(PlayerId winner)
{		
	_gameState->newRound(winner);
}

void GameBoard::addCardToCurrentPlayer(Card* card)
{
}

void GameBoard::playCard()
{	
	//statusValue = VALID_MOVE;
	Card* card = _players[_currentPlayer_id]->play(*_gameState, FIRST_MOVE);
	_gameState->addCardToPlayer(_currentPlayer_id, card);
	int stateValid = 0;

	//while((stateValid = Rules::isStateValid(*_gameState, _players[_currentPlayer_id]->_cards, *card)) != VALID_MOVE)
	//{
		//gs.removeMasterCard();
		card = _players[_currentPlayer_id]->play(*_gameState, stateValid);
		_gameState->addCardToPlayer(_currentPlayer_id, card);
		if( card )
		{
			return;
		}
	//}
	//_players[_currentPlayer_id]->_cards.removeCard(card);

	//UserInterface::showCardPlayed(_players[_currentPlayer_id]->getName(), *card);
}

void GameBoard::addPoint(PlayerId id)
{
	_gameState->addPoint(id);
}

void GameBoard::endRound()
{
	_previousRoundWinner = Rules::getRoundWinner(getGameState());
	_gameState->addPoint(_previousRoundWinner);
	_gameState->newRound(_previousRoundWinner);
	//UserInterface::showRoundWinner(_players[_previousRoundWinner]->_name);
	//UserInterface::showMatchScore(_gameState);	
}

GameState GameBoard::getGameState()
{
	return *_gameState;

}