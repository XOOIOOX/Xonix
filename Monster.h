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

	void advance(int phase);																								// слот апдейта со сцены
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);						// рисовалка итема на сцене

private:
	CentralDataStruct& centralData;
	QPoint positionNew{ BadItemPos };
	QPoint positionOld = positionNew;
	QPointF positionAnimation{ 0.0, 0.0 };
	QPoint direction{ 1, 1 };
	QTimer* positionTimer;
	QTimer* positionAnimationTimer;

	int randomSign();

private slots:
	void positionChangeSlot();
	void positionAnimationSlot();
};
