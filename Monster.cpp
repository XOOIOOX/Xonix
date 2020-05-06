#include "Monster.h"
#include "QPainter"
#include "QColor"

Monster::Monster(CentralDataStruct& data) : QGraphicsEllipseItem(nullptr), centralData(data)
{
	setRect(0, 0, TileSize, TileSize);
	direction = { randomSign(), randomSign() };
	positionNew = { (rand() % (LevelWidth - BorderSizeMonster * 2) + BorderSizeMonster), (rand() % (LevelHeigth - BorderSizeMonster * 2) + BorderSizeMonster) };
	centralData.scene->addItem(this);
	moveCounter = round(animationSteps);
}

Monster::~Monster()
{
	centralData.scene->removeItem(this);
}

void Monster::advance(int phase)
{
	if (!phase)
	{
		if (!moveCounter)
		{
			positionOld = positionNew;

			if ((centralData.matrixCells(positionOld.x() + direction.x(), positionOld.y()) == Full) ||
				 (centralData.matrixCells(positionOld.x() - direction.x(), positionOld.y()) == Full))
			{
				direction.rx() = -direction.x();
			}
			if ((centralData.matrixCells(positionOld.x(), positionOld.y() + direction.y()) == Full )||
				 (centralData.matrixCells(positionOld.x(), positionOld.y() - direction.y()) == Full))
			{
				direction.ry() = -direction.y();
			}

			positionNew = positionOld + direction;
			moveCounter = round(animationSteps);
			positionCorrection = { 0.0, 0.0 };
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