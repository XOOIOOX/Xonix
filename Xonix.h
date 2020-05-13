#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_Xonix.h"
#include "Viewport.h"
#include "GlobalDefs.h"
#include "CentralDataStruct.h"
#include "Track.h"
#include "Monster.h"
#include "Player.h"
#include "Polygon.h"

class Xonix : public QMainWindow
{
	Q_OBJECT

public:
	Xonix(QWidget* parent = Q_NULLPTR);

	void initLandPolygon();

	void showPlayerInfo();

private:
	Ui::Xonix ui;
	Viewport* view;
	CentralDataStruct centralData;
	QTimer* animationTimer;
	Player player{ centralData };
	int currentLevel{ 1 };
	Polygon* landPolygon;
	int allCells{ 0 };
	int capturedCells{ 0 };
	int borderCells{ 0 };
	int capturedPercent{ 0 };
	int score{ 0 };

	void setSceneRect();										// установка размера сцены
	void fillLevelInitial();									// заливка уровня начальной "землей"
	void monsterGenerator();
	void clearMonsters();
	void clearTrack();
	void clearLevel();
	void fillTemp(QPoint point);
	void gameOver();
	int filledCellsCalc();

public slots:
	void collisionSlot();
	void contourCloseSlot();

	void initLevel();
};
