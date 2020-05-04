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
	connect(view, SIGNAL(playerMoveSignal(PlayerDirection)), this, SLOT(playerMoveSlot(PlayerDirection)));

	//////////////////////////////////////////////////////////////////////////
	// ТЕСТ
	//////////////////////////////////////////////////////////////////////////
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

	player.position = { LevelWidth / 2, 0 };
	centralData.scene->addItem(&player);
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

void Xonix::playerMoveSlot(PlayerDirection direction)
{
	auto newPosition = player.position + directionMap[direction];

	if ((newPosition.x() < LevelWidth) &&
		(newPosition.y() < LevelHeigth) &&
		(newPosition.x() >= 0) &&
		(newPosition.y() >= 0))
	{
		switch (cellAccess(newPosition))
		{
			case Empty:
			{
				auto item = new Wall;
				item->setCellType(Temp);
				item->setPosition(newPosition);
				centralData.scene->addItem(item);
				cellAccess(newPosition) = Full;

				break;
			}
			case Full:
			{
				break;
			}
			case Temp:
			{
				break;
			}

			default:
			{ break; }
		}

		player.position = newPosition;
	}

	//////////////////////////////////////////////////////////////////////////
	// ТЕСТ
	//////////////////////////////////////////////////////////////////////////
	ui.playerPosLabel->setText("Player x: " + QString::number(player.position.x()) + "\n" +
						   "Player y: " + QString::number(player.position.y()) + "\n");
	//////////////////////////////////////////////////////////////////////////
}

CellType& Xonix::cellAccess(const QPoint& point) { return centralData.matrixCells(point.x(), point.y()); }

void Xonix::setSceneRect()
{
	QRect rect;
	rect.setWidth(LevelWidth * TileSize);
	rect.setHeight(LevelHeigth * TileSize);
	centralData.scene->setSceneRect(rect);
}