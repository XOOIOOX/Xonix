#include "CentralDataStruct.h"

CellType& CentralDataStruct::cellAccess(const QPoint& point)
{
	return level(point.x(), point.y());
}