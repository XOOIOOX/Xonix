#pragma once

#include <QGraphicsView>
#include "GlobalDefs.h"

class Viewport : public QGraphicsView
{
	Q_OBJECT

public:
	Viewport(QWidget* parent);
	~Viewport();

	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);

private:
	void dumpCoords();

signals:
};
