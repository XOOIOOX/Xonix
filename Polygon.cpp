#include "Polygon.h"
#include "QVector"

Polygon::Polygon(CentralDataStruct& data) : QGraphicsPolygonItem(nullptr), centralData(data)
{
	centralData.scene->addItem(this);
}

Polygon::~Polygon()
{
	scene()->removeItem(this);
}

void Polygon::setCellType(CellType cellType)
{
	type = cellType;
}

void Polygon::setPosition(QPoint pos)
{
	position = pos;
	setPos(position * TileSize);
}

void Polygon::setPolygon(const VectorPoint vec)
{
	polygon = QPolygon(QVector<QPoint>::fromStdVector(vec));
}

void Polygon::unite(const VectorPoint vec)
{
	polygon = polygon.united(QPolygon(QVector<QPoint>::fromStdVector(vec)));
}

void Polygon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	if (type == Land)
	{
		painter->setBrush({ QColor{ Qt::green }, Qt::SolidPattern });
	}
	else
	{
		painter->setBrush({ QColor{ Qt::blue }, Qt::SolidPattern });
	}

	for (auto it : polygon)
	{
		scenePolygon << it * TileSize;
	}

	painter->setPen(Qt::NoPen);
	painter->drawPolygon(scenePolygon);
}