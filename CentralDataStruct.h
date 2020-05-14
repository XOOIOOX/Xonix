#pragma once

#include "GlobalDefs.h"

struct CentralDataStruct
{
	MatrixCells level{ LevelWidth, LevelHeigth, CellType::Water };							// матрица уровня
	QGraphicsScene* scene;																	// сцена для отрисовки
	MonsterList monsterList;																// список монстров
	TrackList trackList;																	// спиское ячеек "трека"

	CellType& cellAccess(const QPoint& point);												// доступ к чейке уровня
};
