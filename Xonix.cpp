#include "Xonix.h"

Xonix::Xonix(QWidget* parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	view = ui.view;

	for (int b = 0; b < BorderSize; b++)
	{
		for (int x = 0; x < LevelWidth; x++)
		{
			centralData.matrixCells(x, b) = Full;
			centralData.matrixCells(x, LevelHeigth - b - 1) = Full;
		}

		for (int y = 0; y < LevelHeigth; y++)
		{
			centralData.matrixCells(b, y) = Full;
			centralData.matrixCells(LevelWidth - b - 1, y) = Full;
		}
	}
}