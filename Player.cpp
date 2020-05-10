#include "Player.h"
#include "QPainter"
#include "Wall.h"

Player::Player(CentralDataStruct& data) : centralData(data), QGraphicsRectItem(nullptr)
{
	setRect(0, 0, TileSize, TileSize);
	moveCounter = round(animationSteps);
	setZValue(10);
}

Player::~Player()
{}

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
		if (moveCounter <= 0)
		{
			positionOld = positionNew;
			moveCounter = round(animationSteps);
			positionCorrection = { 0.0, 0.0 };
			positionNew = positionOld + directionMap[moveDirection];

			if (positionNew.x() < LevelWidth && positionNew.y() < LevelHeigth && positionNew.x() >= 0 && positionNew.y() >= 0)
			{
				if (centralData.cellAccess(positionOld) == Full && centralData.cellAccess(positionNew) == Empty)
				{
					positionBegin = positionOld;
				}

				if (centralData.cellAccess(positionOld) == Temp && centralData.cellAccess(positionNew) == Full)
				{
					positionEnd = positionNew;
					emit contourCloseSignal();
				}

				if ((centralData.cellAccess(positionOld) == Temp || centralData.cellAccess(positionOld) == Full) && centralData.cellAccess(positionNew) == Empty)
				{
					auto wall = makeItem<Wall>(centralData);
					wall->setCellType(Temp);
					wall->setPosition(positionNew);
					centralData.wallsList.push_back(wall);
					directionBlocker = true;
				}
				else
				{
					directionBlocker = false;
				}
			}
			else
			{
				positionNew = positionOld;
				moveDirection = Stop;
			}
		}

		moveCounter--;
		setPos((static_cast<QPointF>(positionNew) + positionCorrection) * static_cast<double>(TileSize));
		positionCorrection += static_cast<QPointF>(directionMap[moveDirection]) / animationSteps;
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
	if (directionBlocker)
	{
		if (((direction == Left || direction == Right) && (moveDirection == Up || moveDirection == Down)) ||
			((direction == Up || direction == Down) && (moveDirection == Left || moveDirection == Right)))
		{
			moveDirection = direction;
		}
	}
	else
	{
		moveDirection = direction;
	}

	std::cout << "old: " << positionOld.x() << " x " << positionOld.y() << " | new: " << positionNew.x() << " x " << positionNew.y() << std::endl;
	std::cout << " item old: " << centralData.cellAccess(positionOld) << " item new: " << centralData.cellAccess(positionNew) << std::endl;
}