#pragma once
#include <qgraphicsitem.h>
#include "GlobalDefs.h"
#include <QPainter>
#include "CentralDataStruct.h"

class Wall : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Wall(CentralDataStruct& data);
	~Wall();

	CellType type{ Land };
	QPoint position{ BadItemPos };

	void setCellType(CellType cellType);
	void setPosition(QPoint pos);
	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);

private:
	CentralDataStruct& centralData;
};
