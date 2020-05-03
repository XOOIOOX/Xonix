#pragma once
#include <qgraphicsitem.h>
#include "GlobalDefs.h"
#include <QPainter>

class Wall : public QGraphicsRectItem, QObject
{
public:

	Wall();
	virtual ~Wall();

	CellType type{ Full };
	QPoint position{ BadItemPos };

	void setCellType(CellType celltype);
	void setPosition(QPoint pos);
	virtual void advance(int phase);									// слот апдейта со сцены
	virtual void paint(QPainter* painter,
					   const QStyleOptionGraphicsItem* option,
					   QWidget* widget = nullptr);						// рисовалка итема на сцене
};
