#include <QMouseEvent>
#include "Viewport.h"
#include <iostream>

Viewport::Viewport(QWidget* parent) : QGraphicsView(parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	setRenderHints(QPainter::Antialiasing);
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
{}