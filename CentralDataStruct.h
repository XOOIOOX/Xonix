#pragma once

#include "GlobalDefs.h"

struct CentralDataStruct
{
	MatrixCells level{ LevelWidth, LevelHeigth, Empty };							// матрица уровня
	QGraphicsScene* scene;															// сцена для отрисовки
	MonsterList monsterList;														// список монстров
	WallList wallsList;																// список стен

	CellType& cellAccess(const QPoint& point);
};
