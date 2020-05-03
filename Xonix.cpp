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
	connect(animationTimer, SIGNAL(timeout()), centralData.scene, SLOT(advance()));

	//////////////////////////////////////////////////////////////////////////
	// ТЕСТ
	//////////////////////////////////////////////////////////////////////////
	centralData.monsterList.push_back(makeItem<Monster>(centralData));
	centralData.monsterList.push_back(makeItem<Monster>(centralData));
	centralData.monsterList.push_back(makeItem<Monster>(centralData));

	centralData.matrixCells(20, 20) = Full;
	centralData.matrixCells(20, 21) = Full;
	centralData.matrixCells(20, 22) = Full;
	centralData.matrixCells(20, 23) = Full;
	centralData.matrixCells(21, 20) = Full;
	centralData.matrixCells(21, 21) = Full;
	centralData.matrixCells(21, 22) = Full;
	centralData.matrixCells(21, 23) = Full;
	centralData.matrixCells(22, 20) = Full;
	centralData.matrixCells(22, 21) = Full;
	centralData.matrixCells(22, 22) = Full;
	centralData.matrixCells(22, 23) = Full;
	//////////////////////////////////////////////////////////////////////////

	fillSceneInitial();
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

void Xonix::clearScene()
{
	auto items = centralData.scene->items();
	for (auto it : items) { centralData.scene->removeItem(it); }
}

void Xonix::fillSceneInitial()
{
	for (int x = 0; x < LevelWidth; x++)
	{
		for (int y = 0; y < LevelHeigth; y++)
		{
			if (centralData.matrixCells(x, y) == Full)
			{
				auto item = new Wall;
				item->setCellType(Full);
				item->setPosition({ x, y });
				centralData.scene->addItem(item);
			}
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