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


GameBoard::GamePhase GameBoard::go()
{	
	//ShowStats();
	switch (_currentGamePhase)
	{
		case StartingRound:
			startNewMatch();
			break;
		case Playing:
			playOneRound();
			break;
		case EndingRound:
			endRound();
			break;
		case FinishingMatch:
			startNewMatch();
			break;
		default:
			break;
	}

	return _currentGamePhase;
}


PlayerId GameBoard::addPlayer(Player* iPlayer, CardinalPosition pos)
{
	PlayerId id = _allPlayersStatus.empty() ? 0 : _players.size();
	_allPlayersStatus[id] = (new PlayerStatus(id, iPlayer->getName(), pos));
	_players[id] = iPlayer;
	return id;
}


void GameBoard::startNewMatch()
{
	
	_matchState = new MatchState(&_allPlayersStatus);
	map<PlayerId, PlayerStatus*>::iterator playersIt = _allPlayersStatus.begin();
	for(;playersIt != _allPlayersStatus.end(); ++playersIt)
	{ 
		(*playersIt).second->reset(Rules::NumberOfInitialCards());
	}
	dealCards();
	defineFirstToPlay();
	//TODO: erase allPlayersStatus
	/*while (Rules::roundsToPlay(*_matchState)>0)
	{
		
		playOneRound();
		isFirstRound=false;
	}
	announceWinner();*/
}


void GameBoard::ShowStats()
{
	map<PlayerId, PlayerStatus*>::iterator playersIt = _allPlayersStatus.begin();
	for(;playersIt != _allPlayersStatus.end(); ++playersIt)
	{ 
		UserInterface::showMatchState((*(*playersIt).second));
	}
}

void GameBoard::playOneRound()
{			

	if ( _currentPlayer_id == -1)
	{
		_currentGamePhase = EndingRound;
	}
	else
	{
		playCard();	
	}
	
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
	return _matchState->_allPlayersCurrentStatus->size();
}

void GameBoard::defineFirstToPlay()
{
	//to randomly choose a player, if there's no defined first player
	int i = randomInt(_players.size());
	
	//TODO: iterate over playerIds (first of map players)
	for(int pIndex = 0;	pIndex < getNumberOfPlayers(); ++pIndex)
	{ 
		if (_matchState->isPlayerFirstToPlay(pIndex))
		{
			i = pIndex;
		}
	}
	_matchState->defineFirstToPlay(i);
	_currentPlayer_id = i;
	//_currentPlayer_id = 1;
}

PlayerStatus* GameBoard::getCurrentPlayerStatus()
{
	return (*_matchState->_allPlayersCurrentStatus)[_currentPlayer_id];
}

Player* GameBoard::getCurrentPlayer()
{
	return _players[_currentPlayer_id];
}

PlayerId GameBoard::getNextPlayer()
{
	_matchState->playerPlays(_currentPlayer_id);
	++_currentPlayer_id;
	//TODO: add list of IDs
	if(getNumberOfPlayers() <= _currentPlayer_id)
	{
		_currentPlayer_id=0;
	}
	if(_matchState->hasPlayerPlayed(_currentPlayer_id))
	{
		_currentPlayer_id = -1;
	}
	return _currentPlayer_id;	
}

void GameBoard::newRound()
{		
	_matchState->newRound(_previousRoundWinner);
	_currentPlayer_id = _previousRoundWinner;
	_matchState->newRound(_previousRoundWinner);
}


void GameBoard::playCard()
{	
	//statusValue = VALID_MOVE;
	Card* card = _players[_currentPlayer_id]->play(*_matchState, FIRST_MOVE);
	int stateValid = 0;

	//while((stateValid = Rules::isStateValid(*_matchState, _players[_currentPlayer_id]->_cards, *card)) != VALID_MOVE)
	//{
		//card = _players[_currentPlayer_id]->play(*_matchState, stateValid);
		//_matchState->addCardToPlayer(_currentPlayer_id, card);
	if(card && (stateValid = Rules::isStateValid(*_matchState, _players[_currentPlayer_id]->_cards, *card)) == VALID_MOVE)
	{
		_matchState->addCardToPlayer(_currentPlayer_id, card);
		card->playCard();
		_players[_currentPlayer_id]->_cards.removeCard(card);
		_players[_currentPlayer_id]->organizeCards();
		getNextPlayer();
		return;
	}
		
	//}
	//

	//UserInterface::showCardPlayed(_players[_currentPlayer_id]->getName(), *card);
}


void GameBoard::endRound()
{
	_previousRoundWinner = Rules::getRoundWinner(getMatchState());
	cleanPlayedCards();	
	addPoint();
	if(Rules::roundsToPlay(*_matchState) != 0)
	{
		newRound();
		_currentGamePhase = Playing;
	}
	else
	{
		processMatchWinner();
		_currentGamePhase = FinishingMatch;
	}
	//UserInterface::showRoundWinner(_players[_previousRoundWinner]->_name);
	//UserInterface::showMatchScore(_matchState);	
}

void GameBoard::cleanPlayedCards()
{
	map<PlayerId, PlayerStatus*>::iterator playersIt = _allPlayersStatus.begin();
	for(;playersIt != _allPlayersStatus.end(); ++playersIt)
	{ 
		Card* card = _matchState->getCardOfPlayer((*playersIt).first);
		card->deactivate();
	}
	
}

MatchState GameBoard::getMatchState()
{
	return *_matchState;
}

void GameBoard::processMatchWinner()
{
	PlayerId winner = Rules::getMatchWinner(*_matchState);
	UserInterface::showMatchWinner(_players[winner]->_name);
}

void GameBoard::addPoint()
{
	_matchState->addPoint(_previousRoundWinner);
}

void GameBoard::addCardToCurrentPlayer(Card* card)
{
}


