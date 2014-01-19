#include "playerHuman.h"
#include "UserInterface.h"
#include "resources.h"

using namespace std;

Card* PlayerHuman::playCard(int invalidErrorMessage)
{ 	
	//UserInterface::showInvalidMoveMessage(invalidErrorMessage);
	//UserInterface::showPlayerCards(getCards());
	CardSet* cards = Rules::getLegalCards(_currentMatchState, getCards());

	cards->makeCardsClickable();

	Card* card = UserInterface::getCardToPlay();
	
	//if ( !card )
	//{
	//	return 0
	//}
	/*while (iPlay < 1 || iPlay > getNumberCards()) 
	{
		UserInterface::showInvalidMoveMessage(invalidErrorMessage, NumberToString(getNumberCards()));
		UserInterface::showPlayerCards(getCards());
		iPlay = UserInterface::getCardToPlay();
	}*/
	//return getCard(iPlay - 1);
	return card;
}

//TODO: make it generic, instead of only cworking for 5 cards
void PlayerHuman::organizeCards()
{
	//float center = WINDOW_WIDTH / 2;
	int numCards = getNumberCards();
	float pos = (WINDOW_WIDTH - (CARD_WIDTH * numCards + (SPACE_BETWEEN_CARDS_X - 1)))/2;
	for (int i = 0; i < numCards; i++, pos= pos + 85)
	{
		Card* card = getCard(i);		  
		card->setPosition(pos, S_CARD_Y);
		card->activate();
	}
}


sf::Vector2f PlayerHuman::getPlayedCardPosition()
{
	sf::Vector2f pos((WINDOW_WIDTH / 2) - (CARD_WIDTH / 2) , S_CARD_Y - CARD_HEIGHT - SPACE_BETWEEN_CARDS_Y);
	return pos;
}

