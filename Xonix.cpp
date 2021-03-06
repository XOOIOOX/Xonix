#include "Xonix.h"
#include <algorithm>
#include <QFontDatabase>

Xonix::Xonix(QWidget* parent) : QMainWindow(parent)
{
	QFontDatabase::addApplicationFont(":/Resources/04B_30__.TTF");										// загрузка шрифта в базу приложения

	ui.setupUi(this);
	view = ui.view;
	centralData.scene = new QGraphicsScene(view->rect(), this);

	initView();
	initLabels();

	animationTimer = new QTimer(this);
	animationTimer->setTimerType(Qt::PreciseTimer);
	animationTimer->start(1000 / AinmationFps);
	connect(animationTimer, &QTimer::timeout, centralData.scene, &QGraphicsScene::advance, Qt::QueuedConnection);
	connect(view, &Viewport::playerMoveSignal, &player, &Player::playerMoveSlot, Qt::QueuedConnection);
	connect(&player, &Player::contourCloseSignal, this, &Xonix::contourCloseSlot, Qt::QueuedConnection);

	landPolygon = new Polygon(centralData);
	initLevel();
	showPlayerInfo();
	centralData.scene->addItem(&player);
}

void Xonix::initLabels()
{
	QFont font;
	font.setFamily("04b");
	font.setPixelSize(18);
	ui.livesLabel->setFont(font);
	ui.scoreLabel->setFont(font);
	ui.capturedLabel->setFont(font);

	ui.scoreLabel->move({view->rect().left() + BorderSize * TileSize, view->rect().bottom()});
	ui.livesLabel->move({ view->rect().center().x() - ui.livesLabel->width() / 2, view->rect().bottom() });
	ui.capturedLabel->move({ view->rect().bottomRight().x() - ui.capturedLabel->width() - BorderSize *TileSize, view->rect().bottom() });
}

void Xonix::initView()
{
	setSceneRect();
	auto viewRect = centralData.scene->sceneRect().toRect();
	auto windowRect = viewRect;
	windowRect.setSize({ viewRect.width(), viewRect.height() + ui.livesLabel->height() });
	this->resize(windowRect.size());
	this->setWindowFlags(Qt::Widget);
	this->setFixedSize(this->size());
	viewRect.moveCenter(rect().center());
	viewRect.moveTop(0);
	view->setGeometry(viewRect);
	view->setScene(centralData.scene);
}

void Xonix::showPlayerInfo()
{
	ui.livesLabel->setText("Lives: " + QString::number(player.lives));
	ui.scoreLabel->setText("Score: " + QString::number(score));
	ui.capturedLabel->setText("Captured: " + QString::number(capturedPercent) + "%");
}

void Xonix::monsterGenerator()
{
	for (int i = 0; i < currentLevel; i++)
	{
		centralData.monsterList.push_back(makeItem<Monster>(centralData));
		connect(&*centralData.monsterList.back(), &Monster::collisionSignal, this, &Xonix::collisionSlot, Qt::QueuedConnection);
	}
}

void Xonix::gameOver()
{
	currentLevel = 1;
	capturedCells = 0;
	score = 0;
	initLevel();
	player.lives = 3;
	showPlayerInfo();
}

void Xonix::collisionSlot()
{
	clearTrack();
	for (auto& it : centralData.level.data()) { if (it == CellType::Track) { it = CellType::Water; } }
	player.setPosition(player.positionBegin);
	player.playerMoveSlot(Stop);
	player.lives--;
	showPlayerInfo();
	if (!player.lives) { gameOver(); }
}

void Xonix::contourCloseSlot()
{
	auto previousCapturedCells = filledCellsCalc() - borderCells;								// количество ранее захваченных ячеек

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

	capturedCells = filledCellsCalc() - borderCells;
	allCells = LevelWidth * LevelHeigth - borderCells;
	capturedPercent = round((static_cast<double>(capturedCells) / static_cast<double>(allCells)) * 100.0);
	score += (capturedCells - previousCapturedCells) * 10;
	if (capturedPercent >= 75) { currentLevel++; initLevel(); }
	showPlayerInfo();
}

void Xonix::initLevel()
{
	clearTrack();
	clearLevel();
	clearMonsters();
	initLandPolygon();
	fillLevelInitial();
	monsterGenerator();
	player.setPosition({ LevelWidth / 2, 0 });
	capturedPercent = 0;
}

int Xonix::filledCellsCalc()
{
	return std::count_if(centralData.level.data().begin(), centralData.level.data().end(), [](auto cell) { return cell == CellType::Land; });
}

void Xonix::fillTemp(QPoint point)
{
	if (centralData.cellAccess(point) != CellType::Water) { return; }
	centralData.cellAccess(point) = CellType::Temp;

	for (int xFill = -1, xIt = xFill; xIt <= 1; xFill = ++xIt)
	{
		for (int yFill = -1, yIt = yFill; yIt <= 1; yFill = ++yIt)
		{
			fillTemp({ point.x() + xFill, point.y() + yFill });
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
			if (centralData.cellAccess({ x, y }) == CellType::Land)
			{
				landPolygon->unite({ { x, y }, { x + 1, y }, { x + 1, y + 1 }, { x, y + 1 } });
			}
		}
	}

	borderCells = filledCellsCalc();
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