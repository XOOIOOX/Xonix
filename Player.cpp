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

			if (((positionOld + directionMap[moveDirection]).x() < LevelWidth) &&
				((positionOld + directionMap[moveDirection]).y() < LevelHeigth) &&
				((positionOld + directionMap[moveDirection]).x() >= 0) &&
				((positionOld + directionMap[moveDirection]).y() >= 0))
			{
				positionNew = positionOld + directionMap[moveDirection];

				if (centralData.cellAccess(positionNew) == Empty && centralData.cellAccess(positionOld) == Full)
				{
					positionBegin = positionOld;
				}

				if (centralData.cellAccess(positionNew) == Full && centralData.cellAccess(positionOld) == Temp)
				{
					positionBegin = positionNew;
					emit contourCloseSignal();
				}

				switch (centralData.cellAccess(positionNew))
				{
					case Empty:
					{
						auto wall = makeItem<Wall>(centralData);
						wall->setCellType(Temp);
						wall->setPosition(positionNew);
						centralData.wallsList.push_back(wall);
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
			}
			else
			{
				moveDirection = Stop;
			}

			std::cout << "old x: " << positionOld.x() << " old y: " << positionOld.y() << "new x: " << positionNew.x() << " new y: " << positionNew.y() << std::endl;
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
	if (direction != Stop && direction != moveDirection)
	{
		moveDirection = direction;
	}
	else
	{
		moveDirection = Stop;
		positionCorrection = { 0.0, 0.0 };
	}
}