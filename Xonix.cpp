#include "Xonix.h"

Xonix::Xonix(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	view = ui.view;
	centralData.scene = new QGraphicsScene(view->rect(), this);
	setSceneRect();
	view->setScene(centralData.scene);

	fillLevelWithBorder();


	animationTimer = new QTimer(this);
	animationTimer->start(1000 / AinmationFps);
}

void Xonix::fillLevelWithBorder()
{
	for (int b = 0; b < BorderSize; b++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			centralData.matrixCells(x, b) = Full;
			centralData.matrixCells(x, LevelHeigth - b - 1) = Full;
		}

		for (int y = 0; y < LevelHeigth; y++)
		{
			centralData.matrixCells(b, y) = Full;
			centralData.matrixCells(LevelWidth - b - 1, y) = Full;
		}
	}
}

void Xonix::setSceneRect()
{
	auto rect = view->rect();
	rect.setWidth(LevelWidth * TileSize);
	rect.setHeight(LevelHeigth * TileSize);
	centralData.scene->setSceneRect(rect);
}