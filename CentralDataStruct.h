#pragma once

#include "GlobalDefs.h"

struct CentralDataStruct
{
	MatrixCells matrixCells{ LevelWidth, LevelHeigth, Empty };							// матрица уровня
	QGraphicsScene* scene;																// сцена для отрисовки
	MonsterList monsterList;															// список мнстров
};
