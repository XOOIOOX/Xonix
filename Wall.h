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
	//Wall(const Wall& wall) : Wall(wall.centralData) {};
	//Wall(Wall&& wall) = default;
	~Wall();

	CellType type{ Full };
	QPoint position{ BadItemPos };

	void setCellType(CellType celltype);
	void setPosition(QPoint pos);
	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);

private:
	CentralDataStruct& centralData;
};
