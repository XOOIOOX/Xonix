#pragma once

#include "GlobalDefs.h"

struct CentralDataStruct
{
	MatrixCells level{ LevelWidth, LevelHeigth, Empty };							// матрица уровня
	QGraphicsScene* scene;																// сцена для отрисовки
	MonsterList monsterList;															// список мнстров

	CellType& cellAccess(const QPoint& point);
};
