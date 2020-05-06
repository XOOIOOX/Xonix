#pragma once
#include <qgraphicsitem.h>
#include <QTimer>
#include "GlobalDefs.h"
#include "CentralDataStruct.h"
#include <utility>

class Monster : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT

public:
	Monster(CentralDataStruct& data);
	Monster(const Monster& monster) = default;
	Monster(Monster&& monster) = default;
	~Monster();

	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
	static int monsterCount;

private:
	CentralDataStruct& centralData;
	QPoint positionNew{ BadItemPos };
	QPoint positionOld = positionNew;
	QPointF positionCorrection{ 0.0, 0.0 };
	QPoint direction{ 1, 1 };
	int moveCounter;
	double animationSteps = static_cast<double>(AinmationFps) / static_cast<double>(MonsterSpeed);

	int randomSign();
signals:
	void collisionSignal();
};
