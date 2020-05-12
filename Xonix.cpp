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
	connect(animationTimer, SIGNAL(timeout()), centralData.scene, SLOT(advance()), Qt::QueuedConnection);
	connect(view, SIGNAL(playerMoveSignal(PlayerDirection)), &player, SLOT(playerMoveSlot(PlayerDirection)));
	connect(&player, SIGNAL(contourCloseSignal()), this, SLOT(contourCloseSlot()), Qt::QueuedConnection);

	landPolygon = new Polygon(centralData);
	landPolygon->setPosition({ 0, 0 });
	landPolygon->setPolygon({ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } });
	fillLevelWithBorder();
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
		connect(&*centralData.monsterList.back(), SIGNAL(collisionSignal()), this, SLOT(collisionSlot()), Qt::QueuedConnection);
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
	clearWallsList();
	//clearScene();
	auto items = centralData.scene->items();
	fillLevelWithBorder();

	clearMonsterList();
	monsterGenerator();

	player.setPosition({ LevelWidth / 2, 0 });
	player.lives = 3;
	showPlayerLives();
}

void Xonix::collisionSlot()
{
	centralData.wallsList.remove_if([](auto& wall) { return wall->type == Track; });
	for (auto& it : centralData.level.data()) { if (it == Track) { it = Water; } }
	player.setPosition(player.positionBegin);
	player.playerMoveSlot(Stop);
	player.lives--;
	showPlayerLives();

	if (!player.lives) { gameOver(); }
}

void Xonix::contourCloseSlot()
{
	for (auto it : centralData.monsterList) { fillTemp(it->getPosition()); }
	for (auto& it : centralData.level.data())
	{
		if (it == Water || it == Track) { it = Land; }
		if (it == Temp) { it = Water; }
	}

	for (auto it : centralData.wallsList) { if (it->type == Track) { centralData.cellAccess(it->position) = Land; } }
	clearWallsList();

	for (int y = 0; y < LevelHeigth; y++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			if (centralData.cellAccess({ x, y }) == Land) { landPolygon->unite({ { x, y }, { x + 1, y }, { x + 1, y + 1 }, { x, y + 1 } }); }
		}
	}

	auto items = centralData.scene->items();
	player.setPosition(player.positionEnd);
	player.playerMoveSlot(Stop);
}

void Xonix::fillTemp(QPoint point)
{
	if (centralData.cellAccess(point) != Water)
	{
		return;
	}

	centralData.cellAccess(point) = Temp;

	for (int n = -1, o = n; o <= 1; n = ++o)
	{
		for (int l = -1, m = l; m <= 1; l = ++m)
		{
			fillTemp({ point.x() + n, point.y() + l });
		}
	}
}

void Xonix::fillLevelWithBorder()
{
	for (int b = 0; b < BorderSize; b++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			centralData.cellAccess({ x, b }) = Land;
			centralData.cellAccess({ x, LevelHeigth - b - 1 }) = Land;

			//makeLand(x, b);
			//makeLand(x, LevelHeigth - b - 1);
		}

		for (int y = 0; y < LevelHeigth; y++)
		{
			centralData.cellAccess({ b, y }) = Land;
			centralData.cellAccess({ LevelWidth - b - 1, y }) = Land;
			//makeLand(b, y);
			//makeLand(LevelWidth - b - 1, y);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// ТЕСТ
	//////////////////////////////////////////////////////////////////////////

	for (int y = 0; y < LevelHeigth; y++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			if (centralData.cellAccess({ x, y }) == Land) { landPolygon->unite({ { x, y }, { x + 1, y }, { x + 1, y + 1 }, { x, y + 1 } }); }
		}
	}
}

void Xonix::clearScene()
{
	auto items = centralData.scene->items();
	for (auto it : items) { centralData.scene->removeItem(it); }
}

void Xonix::makeLand(int x, int y)
{
	auto wall = makeItem<Wall>(centralData);
	wall->setCellType(Land);
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