#include "playerDerp.h"
#include "tools.h"

Card* PlayerDerp::playCard(int invalidErrorMessage)
{   
	CardSet* cards = Rules::getLegalCards(_currentGameState, getCards());
	//cout << "legal cards: " << cards;
	return getCard(randomInt(getNumberCards()));
};
