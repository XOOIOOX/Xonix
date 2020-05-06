#pragma once
#include <qgraphicsitem.h>
#include "GlobalDefs.h"
#include <QPainter>

class Wall : public QGraphicsRectItem, public QObject
{
public:
	Wall();
	virtual ~Wall();

	CellType type{ Full };
	QPoint position{ BadItemPos };

	void setCellType(CellType celltype);
	void setPosition(QPoint pos);
	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
};
