#pragma once
#include <qgraphicsitem.h>
#include <QTimer>
#include "GlobalDefs.h"
#include "CentralDataStruct.h"
#include <utility>

class Monster : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Monster(CentralDataStruct& data);
	~Monster();

	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
	QPoint getPosition();

signals:
	void collisionSignal();

private:
	CentralDataStruct& centralData;
	QPoint positionNew{ BadItemPos };
	QPoint positionOld = positionNew;
	QPointF positionCorrection{ 0.0, 0.0 };
	QPoint direction{ 1, 1 };
	int moveCounter;
	double animationSteps = static_cast<double>(AinmationFps) / static_cast<double>(MonsterSpeed);

	int randomSign();
};
