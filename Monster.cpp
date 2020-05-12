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
	setZValue(2);
}

Monster::~Monster()
{
	disconnect(this, nullptr, nullptr, nullptr);
	scene()->removeItem(this);
}

void Monster::advance(int phase)
{
	if (!phase)
	{
		if (!moveCounter)
		{
			positionOld = positionNew;

			if ((centralData.level(positionOld.x() + direction.x(), positionOld.y()) == CellType::Land) ||
				 (centralData.level(positionOld.x() - direction.x(), positionOld.y()) == CellType::Land))
			{
				direction.rx() = -direction.x();
			}
			if ((centralData.level(positionOld.x(), positionOld.y() + direction.y()) == CellType::Land) ||
				 (centralData.level(positionOld.x(), positionOld.y() - direction.y()) == CellType::Land))
			{
				direction.ry() = -direction.y();
			}

			positionNew = positionOld + direction;
			moveCounter = round(animationSteps);
			positionCorrection = { 0.0, 0.0 };

			if (centralData.cellAccess(positionNew) == CellType::Track)
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

QPoint Monster::getPosition()
{
	return positionNew;
}

int Monster::randomSign() { return rand() % 2 ? 1 : -1; }