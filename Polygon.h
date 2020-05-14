#pragma once

#include "CentralDataStruct.h"
#include "GlobalDefs.h"
#include <QGraphicsPolygonItem>
#include <QPainter>

class Polygon : public QGraphicsRectItem
{
public:
	Polygon(CentralDataStruct& data);
	~Polygon();

	void setPosition(QPoint pos);																			// установка позиции
	void setPolygon(const VectorPoint vec);																	// установка полигона
	void unite(const VectorPoint vec);																		// объединение текущего полигона с новым
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);		

private:
	CellType type{ CellType::Land };																		// тип ячейки (по умолчанию "земля")
	QPoint position{ BadItemPos };																			// позиция на уровне
	CentralDataStruct& centralData;																			// ссылка на общие данные
	QPolygon polygon{ QVector<QPoint> { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } } };							// полигон в координатах уровня
	QPolygon scenePolygon;																					// полигон в координатах сцены
};
