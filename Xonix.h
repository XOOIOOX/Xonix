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

	void showPlayerLives();

private:
	Ui::Xonix ui;
	Viewport* view;
	CentralDataStruct centralData;
	QTimer* animationTimer;
	Player player{ centralData };
	int currentLevel{ 1 };
	Polygon* landPolygon;

	void setSceneRect();										// установка размера сцены
	void fillLevelInitial();									// заливка уровня начальной "землей"
	void monsterGenerator();
	void clearMonsters();
	void clearTrack();
	void fillTemp(QPoint point);
	void gameOver();

public slots:
	void collisionSlot();
	void contourCloseSlot();
};
