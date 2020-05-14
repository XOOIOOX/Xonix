#pragma once

#include "CentralDataStruct.h"
#include "GlobalDefs.h"
#include <QGraphicsEffect>
#include <qgraphicsitem.h>

class Monster : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

public:
	Monster(CentralDataStruct& data);
	~Monster();

	void advance(int phase);
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
	QPoint getPosition();																					// получение позиции монстра

signals:
	void collisionSignal();																					// сигнал столкновения с "треком"

private:
	CentralDataStruct& centralData;																			// ссылка на общие данные
	QPoint positionNew{ BadItemPos };																		// новая позиция монстра
	QPoint positionOld = positionNew;																		// старая позиция монстра
	QPointF positionCorrection{ 0.0, 0.0 };																	// добавочная позиция между ячеек
	QPoint direction{ 1, 1 };																				// направление движения
	int moveCounter;																						// счетчик перемещения
	double animationSteps = static_cast<double>(AinmationFps) / static_cast<double>(MonsterSpeed);			// количество кадров анимации исходя из FPS и скорости монстра

	QColor effectColor = { Qt::green };																		// цвет тенюшки
	QGraphicsDropShadowEffect* effect;																		// объект эффекта тенюшки
	int blurRadius = 40;																					// радиус тенюшки
	double opacity = 0.9;																					// прозрачность тенюшки

	int randomSign();																						// рандом направления перемещения
};
