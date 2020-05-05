#include "CentralDataStruct.h"

CellType& CentralDataStruct::cellAccess(const QPoint& point)
{
	return matrixCells(point.x(), point.y());
}