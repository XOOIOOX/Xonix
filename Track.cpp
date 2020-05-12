#include "Track.h"

Track::Track(CentralDataStruct& data) :QObject(nullptr), QGraphicsRectItem(nullptr), centralData(data)
{
	setRect(0, 0, TileSize, TileSize);
	centralData.scene->addItem(this);
}

Track::~Track()
{
	scene()->removeItem(this);
}

void Track::setPosition(QPoint pos)
{
	position = pos;
	setPos(position * TileSize);
	centralData.cellAccess(position) = CellType::Track;
}

QPoint Track::getPosition()
{
	return position;
}

void Track::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	painter->setBrush({ QColor{ Qt::blue }, Qt::SolidPattern });
	painter->setPen(Qt::NoPen);
	painter->drawRect(rect());
}