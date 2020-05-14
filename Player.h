#pragma once

#include <qgraphicsitem.h>
#include "GlobalDefs.h"
#include "CentralDataStruct.h"

class Player : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Player(CentralDataStruct& data);
	~Player();

	QPoint positionOld{ BadPos, BadPos };																		// старая позиция
	QPoint positionNew = positionOld;																			// новая позиция
	QPoint positionBegin = positionOld;																			// позиция начала захвата
	QPoint positionEnd = positionNew;																			// позиция конца захвата

	int lives{ 3 };																								// количество жизней

	void setPosition(QPoint point);																				// установка позиции
	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);

private:
	Unmap<PlayerDirection, QPoint> directionMap																	// мапа направления движения
	{
		{ Stop, { 0, 0 } },
		{ Left, { -1, 0 } },
		{ Right, { 1, 0 } },
		{ Up, { 0, -1 } },
		{ Down, { 0, 1 } }
	};

	CentralDataStruct& centralData;																				// ссылка на общие данные
	PlayerDirection moveDirection{ Stop };																		// направление движения
	bool directionBlocker{ false };																				// флаг бля блокировки движения в обратную сторону по "треку"
	QPointF positionCorrection{ 0.0, 0.0 };																		// добавочная позиция между ячеек
	int moveCounter;																							// счетчик перемещения
	double animationSteps = static_cast<double>(AinmationFps) / static_cast<double>(PlayerSpeed);				// количество кадров анимации исходя из FPS и скорости игрока

public slots:
	void playerMoveSlot(PlayerDirection direction);																// слот направления движения игрока

signals:
	void contourCloseSignal();																					// сигнал конца захвата "земли"
};
