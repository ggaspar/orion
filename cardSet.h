#include "card.h"
#include <vector>
#include <algorithm>


#ifndef __CARD_SET_H__
#define __CARD_SET_H__

class Game;
class CardSet
{
 public :
	bool hasSuit(const CardSuit cs) const;

	void createDeck();

	int size() const;

	void pushCard(Card* c);

	Card* chooseCard(int i) const;

	void removeCard(Card* card);

	Card* popCard(); 

	//friend ostream& operator<<(ostream &out, const CardSet& cs );

	void shuffle();

	Card* operator[](int index);

	CardSet* getCardsBySuit(CardSuit& CardSuit) const;

 private :
	vector<Card*> cards;
};

#endif
