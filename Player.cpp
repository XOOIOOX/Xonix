#include "Player.h"
#include "QPainter"
#include "Wall.h"

Player::Player(CentralDataStruct& data) : centralData(data), QGraphicsRectItem(nullptr)
{
	setRect(0, 0, TileSize, TileSize);
	moveTimer = new QTimer(this);
	moveTimer->setTimerType(Qt::PreciseTimer);
	moveAnimationTimer = new QTimer(this);
	moveAnimationTimer->setTimerType(Qt::PreciseTimer);

	connect(moveTimer, SIGNAL(timeout()), this, SLOT(positionChangeSlot()));
	connect(moveAnimationTimer, SIGNAL(timeout()), this, SLOT(positionAnimationSlot()));

	setZValue(10);
}

void Player::setPosition(QPoint point)
{
	positionOld = point;
	positionNew = point;
	setPos(point * TileSize);
}

void Player::advance(int phase)
{
	if (!phase)
	{
		setPos((static_cast<QPointF>(positionNew) + positionAnimation) * static_cast<double>(TileSize));
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
	if (direction != Stop && direction != moveDirection)
	{
		moveDirection = direction;
		moveTimer->start(1000 / PlayerSpeed);
	}
}

void Player::positionChangeSlot()
{
	positionOld = positionNew;
	positionAnimation = { 0.0, 0.0 };

	if (((positionOld + directionMap[moveDirection]).x() < LevelWidth) &&
	((positionOld + directionMap[moveDirection]).y() < LevelHeigth) &&
	((positionOld + directionMap[moveDirection]).x() >= 0) &&
	((positionOld + directionMap[moveDirection]).y() >= 0))
	{
		positionNew = positionOld + directionMap[moveDirection];

		switch (centralData.cellAccess(positionNew))
		{
			case Empty:
			{
				auto item = new Wall;
				item->setCellType(Temp);
				item->setPosition(positionNew);
				centralData.scene->addItem(item);
				centralData.cellAccess(positionNew) = Full;

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

		moveAnimationTimer->start((1000 / PlayerSpeed) / PlayerAnimationSteps);
	}
	else
	{
		moveDirection = Stop;
		moveTimer->stop();
	}
}

void Player::positionAnimationSlot()
{
	if (moveDirection != Stop)
	{
		positionAnimation += static_cast<QPointF>(directionMap[moveDirection]) / static_cast<double>(PlayerAnimationSteps);
	}
	else
	{
		moveAnimationTimer->stop();
	}
}