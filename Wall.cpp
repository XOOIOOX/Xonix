#include "Wall.h"

Wall::Wall(CentralDataStruct& data) :QObject(nullptr), QGraphicsRectItem(nullptr), centralData(data)
{
	setRect(0, 0, TileSize, TileSize);
	centralData.scene->addItem(this);
}

Wall::~Wall()
{
	//centralData.cellAccess(position) = Water;
	scene()->removeItem(this);
}

void Wall::setCellType(CellType cellType)
{
	type = cellType;
}

void Wall::setPosition(QPoint pos)
{
	position = pos;
	setPos(position * TileSize);
	centralData.cellAccess(position) = type;
}

void Wall::advance(int phase)
{}

void Wall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	if (type == Land)
	{
		painter->setBrush({ QColor{ Qt::green }, Qt::SolidPattern });
	}
	else
	{
		painter->setBrush({ QColor{ Qt::blue }, Qt::SolidPattern });
	}

	painter->setPen(Qt::NoPen);
	painter->drawRect(rect());
}