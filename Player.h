#pragma once
#include <qgraphicsitem.h>
#include "GlobalDefs.h"
#include "CentralDataStruct.h"
#include "QTimer"

class Player : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Player(CentralDataStruct& data);

	QPoint position{ BadPos, BadPos };
	int lives{ 3 };

	void advance(int phase);																								// слот апдейта со сцены
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);						// рисовалка итема на сцене

private:
	Unmap<PlayerDirection, QPoint> directionMap
	{
		{ Stop, { 0, 0 } },
		{ Left, { -1, 0 } },
		{ Right, { 1, 0 } },
		{ Up, { 0, -1 } },
		{ Down, { 0, 1 } }
	};

	CentralDataStruct& centralData;
	PlayerDirection moveDirection{ Stop };
	QTimer* moveTimer;

public slots:
	void playerMoveSlot(PlayerDirection direction);
};
