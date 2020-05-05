#include "Player.h"
#include "QPainter"
#include "Wall.h"

Player::Player(CentralDataStruct& data) : centralData(data)
{
	setRect(0, 0, TileSize, TileSize);
	moveTimer = new QTimer(this);
	moveTimer->setTimerType(Qt::PreciseTimer);
	moveTimer->start(1000/ PlayerSpeed);
}

void Player::advance(int phase)
{
	if (!phase)
	{
		setPos(position * TileSize);
		setZValue(10);
	}
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	painter->setBrush({ QColor{ Qt::red }, Qt::SolidPattern });
	painter->setPen(Qt::NoPen);
	painter->drawRect(rect());
}

void Player::playerMoveSlot(PlayerDirection direction)
{
	auto newPosition = position + directionMap[direction];

	if ((newPosition.x() < LevelWidth) &&
		(newPosition.y() < LevelHeigth) &&
		(newPosition.x() >= 0) &&
		(newPosition.y() >= 0))
	{
		switch (centralData.cellAccess(newPosition))
		{
			case Empty:
			{
				auto item = new Wall;
				item->setCellType(Temp);
				item->setPosition(newPosition);
				centralData.scene->addItem(item);
				centralData.cellAccess(newPosition) = Full;

				break;
			}
			case Full:
			{
				break;
			}
			case Temp:
			{
				break;
			}

			default:
			{ break; }
		}

		position = newPosition;
	}
}