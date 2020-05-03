#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Xonix.h"
#include "Viewport.h"
#include "GlobalDefs.h"

class Xonix : public QMainWindow
{
	Q_OBJECT

public:
	Xonix(QWidget* parent = Q_NULLPTR);

private:
	Ui::Xonix ui;
};
