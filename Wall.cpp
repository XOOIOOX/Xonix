#include "Wall.h"

Wall::Wall(CentralDataStruct& data) : QGraphicsRectItem(nullptr), centralData(data)
{
	setRect(0, 0, TileSize, TileSize);
	centralData.scene->addItem(this);
}

Wall::~Wall()
{
	centralData.scene->removeItem(this);
	centralData.cellAccess(position) = Empty;

	//if (type == Temp)
	//{
	//	std::cerr << "Wall TEMP dtor" << std::endl;
	//}
	//else if (type == Full)
	//{
	//	std::cerr << "Wall FULL dtor" << std::endl;
	//}
	//else
	//{
	//	std::cerr << "Wall STRANGE dtor" << std::endl;
	//}
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
	if (type == Full)
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