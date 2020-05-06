#include "Wall.h"

Wall::Wall() : QGraphicsRectItem(nullptr)
{
	setRect(0, 0, TileSize, TileSize);
}

Wall::~Wall()
{
	std::cerr << "Wall dtor" << std::endl;
}

void Wall::setCellType(CellType cellType)
{
	type = cellType;
}

void Wall::setPosition(QPoint pos)
{
	position = pos;
	setPos(position * TileSize);
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