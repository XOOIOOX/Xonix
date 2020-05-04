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

private:
	Ui::Xonix ui;
	Viewport* view;
	CentralDataStruct centralData;
	QTimer* animationTimer;
	Player player;

	void setSceneRect();										// установка размера сцены
	void fillLevelWithBorder();									// заливка уровня бордюром
	void clearScene();											// очистка сцены
	void fillSceneInitial();
	CellType& cellAccess(const QPoint& point);

	Unmap<PlayerDirection, QPoint> directionMap
	{
		{ Left, { -1, 0 } },
		{ Right, { 1, 0 } },
		{ Up, { 0, -1 } },
		{ Down, { 0, 1 } }
	};

	


public slots:
	void playerMoveSlot(PlayerDirection direction);
};
