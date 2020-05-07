#include "Xonix.h"
#include <algorithm>

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

	animationTimer = new QTimer(this);
	animationTimer->setTimerType(Qt::PreciseTimer);
	animationTimer->start(1000 / AinmationFps);
	connect(animationTimer, SIGNAL(timeout()), centralData.scene, SLOT(advance()));
	connect(view, SIGNAL(playerMoveSignal(PlayerDirection)), &player, SLOT(playerMoveSlot(PlayerDirection)));
	connect(&player, SIGNAL(contourCloseSignal()), this, SLOT(contourCloseSlot()));

	gameOverTimer = new QTimer(this);
	gameOverTimer->start(2000);
	//connect(gameOverTimer, SIGNAL(timeout()), this, SLOT(gameOver()));
	//fillLevelWithBorder();
	//fillSceneWithWalls();
	monsterGenerator();

	player.setPosition({ LevelWidth / 2, 0 });
	centralData.scene->addItem(&player);
	showPlayerLives();
}

void Xonix::showPlayerLives()
{
	ui.livesLabel->setText("Lives: " + QString::number(player.lives));
}

void Xonix::monsterGenerator()
{
	for (int i = 0; i < currentLevel; i++)
	{
		centralData.monsterList.push_back(makeItem<Monster>(centralData));
		connect(&*centralData.monsterList.back(), SIGNAL(collisionSignal()), this, SLOT(collisionSlot()));
	}
}

void Xonix::clearMonsterList()
{
	if (!centralData.monsterList.empty()) { centralData.monsterList.clear(); }
}

void Xonix::clearWallsList()
{
	if (!centralData.wallsList.empty()) { centralData.wallsList.clear(); }
}

void Xonix::gameOver()
{
	//clearWallsList();
	//clearScene();
	//fillLevelWithBorder();
	//fillSceneWithWalls();

	clearMonsterList();
	monsterGenerator();

	//centralData.monsterList.push_back(makeItem<Monster>(centralData));
	//connect(centralData.monsterList.back().get(), SIGNAL(collisionSignal()), this, SLOT(collisionSlot()));
	//centralData.scene->addItem(&player);
	player.setPosition({ LevelWidth / 2, 0 });
	player.lives = 1;
	showPlayerLives();
}

void Xonix::collisionSlot()
{
	//centralData.wallsList.remove_if([](auto& wall) { return wall->type == Temp; });

	//player.setPosition(player.positionBegin);
	//player.playerMoveSlot(Stop);
	//player.lives--;
	//ui.livesLabel->setText(QString::number(player.lives));
	//gameOver();
	//if (!player.lives)
	//{
	//	gameOver();
	//}

	if (!centralData.monsterList.empty()) { centralData.monsterList.erase(std::prev(centralData.monsterList.end(), 1)); }

	//clearMonsterList();
	//monsterGenerator();

	std::cout << "Beep\nBeeep\nBeeeep" << std::endl;
}

void Xonix::contourCloseSlot()
{}

void Xonix::fillLevelWithBorder()
{
	for (int b = 0; b < BorderSize; b++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			makeWallFull(x, b);
			makeWallFull(x, LevelHeigth - b - 1);
			//centralData.level(x, b) = Full;
			//centralData.level(x, LevelHeigth - b - 1) = Full;
		}

		for (int y = 0; y < LevelHeigth; y++)
		{
			makeWallFull(b, y);
			makeWallFull(LevelWidth - b - 1, y);

			//centralData.level(b, y) = Full;
			//centralData.level(LevelWidth - b - 1, y) = Full;
		}
	}
}

void Xonix::clearScene()
{
	auto items = centralData.scene->items();
	for (auto it : items) { centralData.scene->removeItem(it); }
}

void Xonix::fillSceneWithWalls()
{
	for (int y = 0; y < LevelHeigth; y++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			if (centralData.level(x, y) == Full)
			{
				makeWallFull(x, y);
			}
		}
	}
}

void Xonix::makeWallFull(int x, int y)
{
	auto wall = makeItem<Wall>(centralData);
	wall->setCellType(Full);
	wall->setPosition({ x, y });
	centralData.wallsList.push_back(wall);
}

void Xonix::setSceneRect()
{
	QRect rect;
	rect.setWidth(LevelWidth * TileSize);
	rect.setHeight(LevelHeigth * TileSize);
	centralData.scene->setSceneRect(rect);
}