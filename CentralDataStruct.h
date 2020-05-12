#pragma once

#include "GlobalDefs.h"

struct CentralDataStruct
{
	MatrixCells level{ LevelWidth, LevelHeigth, CellType::Water };							// матрица уровня
	QGraphicsScene* scene;															// сцена для отрисовки
	MonsterList monsterList;														// список монстров
	WallList trackList;																// список стен

	CellType& cellAccess(const QPoint& point);
};
