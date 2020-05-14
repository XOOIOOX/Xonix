#pragma once

#include "GlobalDefs.h"
#include <QGraphicsView>

class Viewport : public QGraphicsView
{
	Q_OBJECT

public:
	Viewport(QWidget* parent);
	~Viewport();

	void keyPressEvent(QKeyEvent* event);										// ивент нажания кнопки
	void keyReleaseEvent(QKeyEvent* event);										// ивент отпускания кнопки

signals:
	void playerMoveSignal(PlayerDirection direction);							// сигнал для перемещения игрока
};
