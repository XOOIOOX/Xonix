#pragma once
#include "GlobalDefs.h"
#include <QPainter>
#include "CentralDataStruct.h"
#include <QGraphicsPolygonItem>

class Polygon : public QGraphicsPolygonItem
{
public:
	Polygon(CentralDataStruct& data);
	~Polygon();

	void setCellType(CellType cellType);
	void setPosition(QPoint pos);
	void setPolygon(const VectorPoint vec);
	void unite(const VectorPoint vec);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);

private:
	CellType type{ Land };
	QPoint position{ BadItemPos };
	CentralDataStruct& centralData;
	QPolygon polygon{ QVector<QPoint> { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } } };
	QPolygon scenePolygon;
};
