#include <string>
#include "player.h"

Card* Player::play(MatchState& iMatchState, int invalidErrorMessage)
{
	_currentMatchState = iMatchState;
	Card* c = playCard(invalidErrorMessage);
	return c;
}

Card* Player::getCard(int index)
{
	return _cards[index];
}

int Player::getNumberCards()
{
	return _cards.size();
}

bool Player::hasCards()
{
	return _cards.size()>0;
}
const CardSet& Player::getCards() const
{
	return (const CardSet&)_cards;
}
void Player::addOtherPlayerDeck(CardSet* cards)
{
	otherPlayerCards=cards;
}
string Player::getName() const
{
	return _name;
}

void Player::receiveCard(Card* c)
{
	_cards.pushCard(c);
	c->setPlayedPosition(getPlayedCardPosition());
}

