#pragma once
#include <qgraphicsitem.h>
#include "GlobalDefs.h"

class Player : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Player();

	QPoint position{ BadPos, BadPos };
	int lives{ 3 };

	void advance(int phase);																								// слот апдейта со сцены
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);						// рисовалка итема на сцене
};
