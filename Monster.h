#pragma once
#include <qgraphicsitem.h>
#include <QTimer>
#include "GlobalDefs.h"
#include "CentralDataStruct.h"

class Monster : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT

public:
	Monster(CentralDataStruct& data);
	Monster(const Monster& monster) : Monster(monster.centralData) {};
	Monster(Monster&& monster) = default;
	virtual ~Monster();

	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);

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
