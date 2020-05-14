#include "Viewport.h"
#include "qevent.h"

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
	if (!event->isAutoRepeat())
	{
		switch (static_cast<Qt::Key>(event->key()))
		{
			case Qt::Key_Left:
			{
				emit playerMoveSignal(Left);
				break;
			}

			case Qt::Key_Right:
			{
				emit playerMoveSignal(Right);
				break;
			}

			case Qt::Key_Up:
			{
				emit playerMoveSignal(Up);
				break;
			}

			case Qt::Key_Down:
			{
				emit playerMoveSignal(Down);
				break;
			}

			default:
			{ break; }
		}
	}
}

void Viewport::keyReleaseEvent(QKeyEvent* event)
{}