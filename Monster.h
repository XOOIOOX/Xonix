#pragma once
#include <qgraphicsitem.h>
#include <QTimer>
#include "GlobalDefs.h"
#include "CentralDataStruct.h"

class Monster : public QObject, QGraphicsEllipseItem
{
	Q_OBJECT

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
	QTimer* positionTimer;

	int randomSign();

private slots:
	void positionChangeSlot();
};
