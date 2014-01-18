#include <vector>
#include <algorithm>
#include "cardSet.h"
#include "tools.h"
#include "game.h"



bool CardSet::hasSuit(const CardSuit cs) const
{
	vector<Card*>::const_iterator csit;
	for ( csit = cards.begin(); csit!=cards.end(); ++csit)
	{
	    if(cs==(*csit)->_suit)
	    {
	    return true;
	    }
	}
	return false;
}

void CardSet::createDeck()
{
	char suits[4] = { 'D', 'C', 'S', 'H' }; 
	//char faces[13] = {'2','3','4','5','6','7','8','9','T','J','Q','R','A'};
	//int ranks[13] = {2,3,4,5,6,7,8,9,10,11,12,13,14};
	char faces[5] = {'T','J','Q','K','A'};
	int ranks[5] = {1,2,3,4,5};
	
	int isuits, ifaces, iranks;
	for( isuits = 0; isuits != 4; ++isuits)
	{
	    for( ifaces = 0, iranks = 0; ifaces != 5; ++ifaces, ++iranks)
	    {
			Card* card = new Card(faces[ifaces],suits[isuits],ranks[iranks]);		
	//_c1.SetPosition((800/2)-45,500);
			pushCard(card);
			Game::_gameObjectManager.add(card->getCardName(),card);
	    }
	}
}

int CardSet::size() const
{
	return cards.size();
}
  
void CardSet::pushCard(Card* c)
{
	cards.push_back(c);
}
Card* CardSet::chooseCard(int i) const
{
	return cards[i];
}
  
void CardSet::removeCard(Card* card)
{
	cards.erase(remove(cards.begin(), cards.end(), card), cards.end());
}

Card* CardSet::popCard()
{
	Card* card = chooseCard(cards.size()-1);
	removeCard(card);
	return card;
}  
  
void CardSet::shuffle()
{
	random_shuffle(cards.begin(), cards.end(), randomInt);
}
  
Card* CardSet::operator[](int index)
{
	return cards[index];
}

CardSet* CardSet::getCardsBySuit(CardSuit& iCardSuit) const
{
	CardSet* cardSetOfSuit = new CardSet();	

	for(vector<Card*>::const_iterator itCards = cards.begin(); itCards!= cards.end(); ++itCards)
	{
		if((*itCards)->_suit == iCardSuit)
		{
			cardSetOfSuit->pushCard(*itCards);
		}
	}	
	return cardSetOfSuit;
}

