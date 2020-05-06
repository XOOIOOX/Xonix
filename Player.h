#pragma once
#include <qgraphicsitem.h>
#include "GlobalDefs.h"
#include "CentralDataStruct.h"
#include "QTimer"
#include <queue>

class Player : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Player(CentralDataStruct& data);
	~Player();

	QPoint positionOld{ BadPos, BadPos };
	QPoint positionNew = positionOld;
	QPoint positionBegin = positionOld;
	int lives{ 3 };

	void setPosition(QPoint point);
	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);

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
	QTimer* moveAnimationTimer;
	QPointF positionAnimation{ 0.0, 0.0 };


public slots:
	void playerMoveSlot(PlayerDirection direction);
	void positionChangeSlot();
	void positionAnimationSlot();

signals:
	void contourCloseSignal();
};
