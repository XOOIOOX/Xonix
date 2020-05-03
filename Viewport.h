#pragma once

#include <QGraphicsView>
#include "GlobalDefs.h"

class Viewport : public QGraphicsView
{
	Q_OBJECT

public:
	Viewport(QWidget* parent);
	~Viewport();

	//void mousePressEvent(QMouseEvent* event);
	//void mouseReleaseEvent(QMouseEvent* event);
	//void mouseMoveEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

private:

	void dumpCoords();

signals:
	void deltaChangedXySignal(int deltaX, int deltaY);
	void mousePositionSignal(QPoint pos);
	void itemDeleteSignal();
	void itemAddSignal();
};
