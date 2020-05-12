#pragma once
#include <qgraphicsitem.h>
#include "GlobalDefs.h"
#include <QPainter>
#include "CentralDataStruct.h"

class Track : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Track(CentralDataStruct& data);
	~Track();

	void setPosition(QPoint pos);
	QPoint getPosition();
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);

private:
	CentralDataStruct& centralData;
	QPoint position{ BadItemPos };
};
