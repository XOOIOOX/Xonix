#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_Xonix.h"
#include "Viewport.h"
#include "GlobalDefs.h"
#include "CentralDataStruct.h"
#include "Wall.h"
#include "Monster.h"
#include "Player.h"

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
	int currentLevel{ 2 };

	void setSceneRect();										// установка размера сцены
	void fillLevelWithBorder();									// заливка уровня бордюром
	void clearScene();											// очистка сцены
	void fillSceneWithWalls();
	void monsterGenerator();
	void clearMonsterList();
	void clearWallsList();
	void gameOver();

public slots:
	void collisionSlot();
	void contourCloseSlot();
};
