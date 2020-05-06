#include "Xonix.h"

Xonix::Xonix(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	view = ui.view;
	centralData.scene = new QGraphicsScene(view->rect(), this);
	setSceneRect();
	auto viewRect = centralData.scene->sceneRect().toRect();
	//viewRect.moveCenter(rect().center());
	view->setGeometry(viewRect);
	view->setScene(centralData.scene);

	fillLevelWithBorder();

	animationTimer = new QTimer(this);
	animationTimer->setTimerType(Qt::PreciseTimer);
	animationTimer->start(1000 / AinmationFps);
	connect(animationTimer, SIGNAL(timeout()), centralData.scene, SLOT(advance()));
	connect(view, SIGNAL(playerMoveSignal(PlayerDirection)), &player, SLOT(playerMoveSlot(PlayerDirection)));

	fillSceneInitial();
	monsterGenerator();

	player.setPosition({ LevelWidth / 2, 0 });
	centralData.scene->addItem(&player);
}

void Xonix::monsterGenerator()
{
	for (int i = 0; i < currentLevel; i++)
	{
		centralData.monsterList.push_back(makeItem<Monster>(centralData));
	}
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
	QRect rect;
	rect.setWidth(LevelWidth * TileSize);
	rect.setHeight(LevelHeigth * TileSize);
	centralData.scene->setSceneRect(rect);
}