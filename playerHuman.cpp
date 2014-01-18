#include "playerHuman.h"
#include "UserInterface.h"

using namespace std;

Card* PlayerHuman::playCard(int invalidErrorMessage)
{ 	
	//UserInterface::showInvalidMoveMessage(invalidErrorMessage);
	//UserInterface::showPlayerCards(getCards());
	VisibleGameObject* object = UserInterface::getCardToPlay();
	Card* card = dynamic_cast<Card*>(object);
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
