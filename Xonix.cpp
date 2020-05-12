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
	initLandPolygon();

	fillLevelInitial();
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

void Xonix::gameOver()
{
	clearTrack();
	clearLevel();
	clearMonsters();
	initLandPolygon();
	fillLevelInitial();
	monsterGenerator();
	player.setPosition({ LevelWidth / 2, 0 });
	player.lives = 3;
	showPlayerLives();
}

void Xonix::collisionSlot()
{
	clearTrack();
	for (auto& it : centralData.level.data()) { if (it == CellType::Track) { it = CellType::Water; } }
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
		if (it == CellType::Water || it == CellType::Track) { it = CellType::Land; }
		if (it == CellType::Temp) { it = CellType::Water; }
	}

	for (auto it : centralData.trackList) { centralData.cellAccess(it->getPosition()) = CellType::Land; }
	clearTrack();

	for (int y = 0; y < LevelHeigth; y++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			if (centralData.cellAccess({ x, y }) == CellType::Land) { landPolygon->unite({ { x, y }, { x + 1, y }, { x + 1, y + 1 }, { x, y + 1 } }); }
		}
	}

	player.setPosition(player.positionEnd);
	player.playerMoveSlot(Stop);
}

void Xonix::fillTemp(QPoint point)
{
	if (centralData.cellAccess(point) != CellType::Water)
	{
		return;
	}

	centralData.cellAccess(point) = CellType::Temp;

	for (int n = -1, o = n; o <= 1; n = ++o)
	{
		for (int l = -1, m = l; m <= 1; l = ++m)
		{
			fillTemp({ point.x() + n, point.y() + l });
		}
	}
}

void Xonix::fillLevelInitial()
{
	for (int b = 0; b < BorderSize; b++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			centralData.cellAccess({ x, b }) = CellType::Land;
			centralData.cellAccess({ x, LevelHeigth - b - 1 }) = CellType::Land;
		}

		for (int y = 0; y < LevelHeigth; y++)
		{
			centralData.cellAccess({ b, y }) = CellType::Land;
			centralData.cellAccess({ LevelWidth - b - 1, y }) = CellType::Land;
		}
	}

	for (int y = 0; y < LevelHeigth; y++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			if (centralData.cellAccess({ x, y }) == CellType::Land) { landPolygon->unite({ { x, y }, { x + 1, y }, { x + 1, y + 1 }, { x, y + 1 } }); }
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

void Xonix::clearMonsters()
{
	if (!centralData.monsterList.empty()) { centralData.monsterList.clear(); }
}

void Xonix::clearTrack()
{
	if (!centralData.trackList.empty()) { centralData.trackList.clear(); }
}

void Xonix::clearLevel()
{
	for (auto& it : centralData.level.data()) { it = CellType::Water; }
}

void Xonix::initLandPolygon()
{
	landPolygon->setPosition({ 0, 0 });
	landPolygon->setPolygon({ { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } });
}