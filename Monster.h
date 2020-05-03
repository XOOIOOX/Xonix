#pragma once
#include <qgraphicsitem.h>
#include "GlobalDefs.h"
#include "CentralDataStruct.h"

class Monster : public QGraphicsEllipseItem, QObject
{
public:
	Monster(CentralDataStruct& data);
	Monster(const Monster& monster) : Monster(monster.centralData) {};
	Monster(Monster&& monster) = default;
	virtual ~Monster();

	void advance(int phase);											// слот апдейта со сцены
	void paint(QPainter* painter,
					   const QStyleOptionGraphicsItem* option,
					   QWidget* widget = nullptr);						// рисовалка итема на сцене

private:
	CentralDataStruct& centralData;
	QPoint position{ BadItemPos };
	QPoint direction{ 1, 1 };
	//Unmap<MonsterDirection, QPoint> directionMap
	//{
	//	{ LeftUp, { -1, -1 } },
	//	{ LeftDown, { -1, 1 } },
	//	{ RightUp, { 1, -1 } },
	//	{ RightDown, { 1, 1 } }
	//};

	int randomSign();
};
