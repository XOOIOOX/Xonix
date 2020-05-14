#pragma once

#include "CentralDataStruct.h"
#include "GlobalDefs.h"
#include <QGraphicsEffect>
#include <qgraphicsitem.h>
#include <QPainter>

class Track : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Track(CentralDataStruct& data);
	~Track();

	void setPosition(QPoint pos);																				// установка позиции
	QPoint getPosition();																						// считывание позиции
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);

private:
	CentralDataStruct& centralData;																				// ссылка на общие данные
	QPoint position{ BadItemPos };																				// позиция на уровне
};
