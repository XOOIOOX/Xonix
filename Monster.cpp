#include "Monster.h"
#include "QPainter"
#include "QColor"

Monster::Monster(CentralDataStruct& data) : QGraphicsEllipseItem(nullptr), centralData(data)
{
	setRect(0, 0, TileSize, TileSize);
	direction = { randomSign(), randomSign() };
	position = { (rand() % (LevelWidth - BorderSizeMonster * 2) + BorderSizeMonster), (rand() % (LevelHeigth - BorderSizeMonster * 2) + BorderSizeMonster) };
	centralData.scene->addItem(this);
	positionTimer = new QTimer(this);
	positionTimer->start(MonsterTimer);
	connect(positionTimer, SIGNAL(timeout()), this, SLOT(positionChangeSlot()));
}

Monster::~Monster()
{
	centralData.scene->removeItem(this);
}

void Monster::advance(int phase)
{
}

void Monster::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	painter->setBrush(QBrush{ Qt::black, Qt::SolidPattern });
	painter->drawEllipse(rect());
}

int Monster::randomSign() { return rand() % 2 ? 1 : -1; }

void Monster::positionChangeSlot()
{
	if ((centralData.matrixCells(position.x() + direction.x(), position.y()) || (centralData.matrixCells(position.x() - direction.x(), position.y()))) == Full)
	{
		direction.rx() = -direction.x();
	}
	if ((centralData.matrixCells(position.x(), position.y() + direction.y()) || (centralData.matrixCells(position.x(), position.y() - direction.y()))) == Full)
	{
		direction.ry() = -direction.y();
	}

	position += direction;
	setPos(position * TileSize);
}