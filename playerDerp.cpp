#include "playerDerp.h"
#include "tools.h"

Card* PlayerDerp::playCard(int invalidErrorMessage)
{   
	CardSet* cards = Rules::getLegalCards(_currentMatchState, getCards());
	//cout << "legal cards: " << cards;
	Card* card = getCard(randomInt(getNumberCards()));
	card->activate();
	return card;

};


sf::Vector2f PlayerDerp::getPlayedCardPosition()
{
	sf::Vector2f pos((WINDOW_WIDTH / 2) - (CARD_WIDTH / 2) , N_CARD_Y + CARD_HEIGHT + SPACE_BETWEEN_CARDS_Y);
	return pos;
}

void PlayerDerp::organizeCards()
{	
	//float center = WINDOW_WIDTH / 2;
	int numCards = getNumberCards();
	float pos = (WINDOW_WIDTH - (CARD_WIDTH * numCards + (SPACE_BETWEEN_CARDS_X - 1)))/2;
	for (int i = 0; i < numCards; i++, pos= pos + 85)
	{
		Card* card = getCard(i);		  
		card->setPosition(pos, N_CARD_Y);
		card->activate();
	}
}
