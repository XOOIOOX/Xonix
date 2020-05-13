#include "Polygon.h"
#include "QVector"

Polygon::Polygon(CentralDataStruct& data) : QGraphicsRectItem(nullptr), centralData(data)
{
	centralData.scene->addItem(this);
	setZValue(0);
}

Polygon::~Polygon()
{
	scene()->removeItem(this);
}

void Polygon::setCellType(CellType cellType)
{
	type = cellType;
	update();
}

void Polygon::setPosition(QPoint pos)
{
	position = pos;
	setPos(position * TileSize);
}

void Polygon::setPolygon(const VectorPoint vec)
{
	polygon = QPolygon(QVector<QPoint>::fromStdVector(vec));
	update();
}

void Polygon::unite(const VectorPoint vec)
{
	polygon = polygon.united(QPolygon(QVector<QPoint>::fromStdVector(vec)));
	update();
}

void Polygon::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{
	if (type == CellType::Land)
	{
		painter->setBrush({ QColor{ 255, 170, 255 }, Qt::DiagCrossPattern });
	}
	else
	{
		painter->setBrush({ QColor{ Qt::blue }, Qt::DiagCrossPattern });
	}

	scenePolygon.clear();
	for (auto it : polygon) { scenePolygon << it * TileSize; }
	setRect(scenePolygon.boundingRect());
	painter->setPen(Qt::NoPen);
	painter->drawPolygon(scenePolygon);
}