#include "Monster.h"
#include "QPainter"
#include "QColor"

Monster::Monster(CentralDataStruct& data) : QObject(nullptr), QGraphicsRectItem(nullptr), centralData(data)
{
	setRect(0, 0, TileSize, TileSize);
	direction = { randomSign(), randomSign() };
	positionNew = { (rand() % (LevelWidth - BorderSizeMonster * 2) + BorderSizeMonster), (rand() % (LevelHeigth - BorderSizeMonster * 2) + BorderSizeMonster) };
	positionOld = positionNew;
	moveCounter = round(animationSteps);
	centralData.scene->addItem(this);
}

Monster::~Monster()
{
	//disconnect(this, nullptr, nullptr, nullptr);
	scene()->removeItem(this);
	deleteLater();
}

void Monster::advance(int phase)
{
	if (!phase)
	{
		if (!moveCounter)
		{
			positionOld = positionNew;

			if (positionOld.x() + direction.x() < 1 || positionOld.x() + direction.x() > LevelWidth - 1)
			{
				direction.rx() = -direction.x();
			}

			if (positionOld.y() + direction.y() < 1 || positionOld.y() + direction.y() > LevelHeigth - 1)
			{
				direction.ry() = -direction.y();
			}

			//if ((centralData.level(positionOld.x() + direction.x(), positionOld.y()) == Full) ||
			//	 (centralData.level(positionOld.x() - direction.x(), positionOld.y()) == Full))
			//{
			//	direction.rx() = -direction.x();
			//}
			//if ((centralData.level(positionOld.x(), positionOld.y() + direction.y()) == Full) ||
			//	 (centralData.level(positionOld.x(), positionOld.y() - direction.y()) == Full))
			//{
			//	direction.ry() = -direction.y();
			//}

			positionNew = positionOld + direction;
			moveCounter = round(animationSteps);
			positionCorrection = { 0.0, 0.0 };

			if (centralData.cellAccess(positionNew) == Temp)
			{
				emit collisionSignal();
			}
		}

		moveCounter--;

		setPos((static_cast<QPointF>(positionOld) + positionCorrection) * TileSize);
		positionCorrection += static_cast<QPointF>(direction) / animationSteps;
	}
}

void Monster::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	painter->setBrush(QBrush{ Qt::black, Qt::SolidPattern });
	painter->drawEllipse(rect());
}

int Monster::randomSign() { return rand() % 2 ? 1 : -1; }