#pragma once

#include "ui_Xonix.h"
#include "CentralDataStruct.h"
#include "GlobalDefs.h"
#include "Monster.h"
#include "Player.h"
#include "Polygon.h"
#include "Track.h"
#include "Viewport.h"
#include <QMainWindow>
#include <QTimer>

class Xonix : public QMainWindow
{
	Q_OBJECT

public:
	Xonix(QWidget* parent = Q_NULLPTR);

private:
	Ui::Xonix ui;												// интерфейс игры
	Viewport* view;												// объект вьюшки
	CentralDataStruct centralData;								// общие данные
	QTimer* animationTimer;										// таймер анимации
	Player player{ centralData };								// объект игрока
	int currentLevel{ 1 };										// текущий урвень
	Polygon* landPolygon;										// полигон "земли"
	int allCells{ 0 };											// общее количество ячеек уровня
	int capturedCells{ 0 };										// количество захваченных ячеек
	int borderCells{ 0 };										// количество ячее бордюра
	int capturedPercent{ 0 };									// процент захваченных ячеекк
	int score{ 0 };												// очки

	void setSceneRect();										// установка размера сцены
	void fillLevelInitial();									// заливка уровня начальной "землей"
	void monsterGenerator();									// генерация монстров
	void clearMonsters();										// очистка списка мостров
	void clearTrack();											// очистка "трека"
	void clearLevel();											// очистка уровня
	void fillTemp(QPoint point);								// заливка временными ячейками от монстра
	void gameOver();											// конец игры
	void initLabels();											// подготовка надписей
	void initView();											// подготовка вьюшки
	void initLandPolygon();										// начальная инициализация полигона "земли"
	void showPlayerInfo();										// отображение информации игрока
	void initLevel();											// инициализация уровня
	int filledCellsCalc();										// подсчет количества захваченных ячеек

public slots:
	void collisionSlot();										// слот столкновения монстра и "трека"
	void contourCloseSlot();									// слот захвата игроком "земли"
};
