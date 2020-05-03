#include <QMouseEvent>
#include "Viewport.h"
#include <iostream>

Viewport::Viewport(QWidget* parent) : QGraphicsView(parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setRenderHints(QPainter::LosslessImageRendering);
	setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}

Viewport::~Viewport()
{}



void Viewport::keyPressEvent(QKeyEvent* event)
{
	if (static_cast<Qt::Key>(event->key()) == Qt::Key_Space)
	{
	}
}

void Viewport::keyReleaseEvent(QKeyEvent* event)
{
	if (static_cast<Qt::Key>(event->key()) == Qt::Key_Space)
	{
	}
}

void Viewport::dumpCoords()
{
	//emit deltaChangedXySignal(delta.x(), delta.y());
}