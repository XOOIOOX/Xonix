#include "Player.h"
#include "QPainter"

Player::Player()
{
	setRect(0, 0, TileSize, TileSize);
}

void Player::advance(int phase)
{
	if (!phase)
	{
		setPos(position * TileSize);
	}
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	painter->setBrush({ QColor{ Qt::green }, Qt::SolidPattern });
	painter->setPen(Qt::NoPen);
	painter->drawRect(rect());
}