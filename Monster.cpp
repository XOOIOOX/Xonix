#include "Monster.h"
#include "QPainter"
#include "QColor"

Monster::Monster(CentralDataStruct& data) : QGraphicsEllipseItem(nullptr), centralData(data)
{
	setRect(0, 0, TileSize, TileSize);
	direction = { randomSign(), randomSign() };
	positionNew = { (rand() % (LevelWidth - BorderSizeMonster * 2) + BorderSizeMonster), (rand() % (LevelHeigth - BorderSizeMonster * 2) + BorderSizeMonster) };
	centralData.scene->addItem(this);
	moveTimer = new QTimer(this);
	moveAnimationTimer = new QTimer(this);
	moveTimer->setTimerType(Qt::PreciseTimer);
	moveAnimationTimer->setTimerType(Qt::PreciseTimer);
	moveTimer->start(1000 / MonsterSpeed);
	connect(moveTimer, SIGNAL(timeout()), this, SLOT(positionChangeSlot()));
	connect(moveAnimationTimer, SIGNAL(timeout()), this, SLOT(positionAnimationSlot()));
}

Monster::~Monster()
{
	centralData.scene->removeItem(this);
}

void Monster::advance(int phase)
{
	if (!phase)
	{
		setPos(static_cast<QPointF>(positionOld * TileSize) + positionAnimation);
	}
}

void Monster::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	painter->setBrush(QBrush{ Qt::black, Qt::SolidPattern });
	painter->drawEllipse(rect());
}

void Monster::positionChangeSlot()
{
	positionOld = positionNew;
	positionAnimation = { 0.0, 0.0 };

	if ((centralData.matrixCells(positionOld.x() + direction.x(), positionOld.y()) ||
		 (centralData.matrixCells(positionOld.x() - direction.x(), positionOld.y()))) == Full)
	{
		direction.rx() = -direction.x();
	}
	if ((centralData.matrixCells(positionOld.x(), positionOld.y() + direction.y()) ||
		 (centralData.matrixCells(positionOld.x(), positionOld.y() - direction.y()))) == Full)
	{
		direction.ry() = -direction.y();
	}

	positionNew = positionOld + direction;
	moveAnimationTimer->start((1000 / MonsterSpeed) / MonsterAnimationSteps);
}

void Monster::positionAnimationSlot()
{
	positionAnimation += (static_cast<QPointF>(direction * TileSize)) / static_cast<double>(MonsterAnimationSteps);
}

int Monster::randomSign() { return rand() % 2 ? 1 : -1; }