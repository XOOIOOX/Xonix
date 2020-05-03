#include "Wall.h"

Wall::Wall()
{
	setRect(0, 0, TileSize, TileSize);
}

Wall::~Wall() {}

void Wall::setCellType(CellType cellType)
{
	type = cellType;
}

void Wall::setPosition(QPoint pos)
{
	position = pos;
}

void Wall::advance(int phase)
{
	if (phase) { setPos(position * TileSize); }
}

void Wall::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	if (type == Full)
	{
		painter->setBrush({ QColor{ Qt::red }, Qt::SolidPattern });
	}
	else
	{
		painter->setBrush({ QColor{ Qt::blue }, Qt::SolidPattern });
	}

	painter->setPen(Qt::NoPen);
	painter->drawRect(rect());
}