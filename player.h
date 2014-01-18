// #include "gameStatus.h"
#include <string>
#include "cardSet.h"
#include "rules.h"

#ifndef __PLAYER_H__
#define __PLAYER_H__



class Player
{
 friend class GameBoard;
 public:
  Player(string name) : _name(name) {};
  
  Card* play(GameState& iGameState, int invalidErrorMessage);	  
  
  virtual Card* playCard(int invalidErrorMessage) = 0;

  Card* getCard(int index);

  int getNumberCards();

  bool hasCards();

  const CardSet& getCards() const;

  void addOtherPlayerDeck(CardSet* cards);

  string getName() const;

  GameState _currentGameState;

  virtual void organizeCards() = 0;
 
 private : 
  void receiveCard(Card* c);
  CardSet* otherPlayerCards;
  CardSet _cards;
  string _name;
  PlayerId _id;
};

#endif
