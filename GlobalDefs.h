#pragma once

#include <vector>
#include <list>
#include <boost/numeric/ublas/matrix.hpp>
#include <QPoint>
#include <QSize>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QRect>
#include <QGraphicsScene>
#include <type_traits>
#include <memory>
#include <unordered_map>

//////////////////////////////////////////////////////////////////////////
// Предварительные объявы
//////////////////////////////////////////////////////////////////////////
class Monster;

//////////////////////////////////////////////////////////////////////////
// Константы
//////////////////////////////////////////////////////////////////////////

constexpr auto LevelWidth = 80;															// ширина уровня в тайлах
constexpr auto LevelHeigth = 40;														// высота уровня в тайлах
constexpr auto TileSize = 8;															// размер тайла
constexpr auto BorderSize = 4;															// размер начального бордюра
constexpr auto BorderSizeMonster = BorderSize + 1;										// размер начального бордюра для монстров
constexpr auto AinmationFps = 60;														// кадров в секунду
constexpr auto MonsterTimer = 20;														// интервал действия монстра (мс)
constexpr auto BadPos = -1;																// неверная позиция 
constexpr QPoint BadItemPos = QPoint{ BadPos, BadPos };									// неверная позиция итема


//////////////////////////////////////////////////////////////////////////
// Общие енумы
//////////////////////////////////////////////////////////////////////////

enum PlayerDirection																	// направление движения игрока
{
	Left, Right, Up, Down
};

enum CellType																			// содержимое ячейки
{
	Empty,																				// пустая
	Full,																				// откушенная
	Temp																				// занятая, но не откушенная
};

template<typename T> using Vector = std::vector<T>;
template<typename T> using List = std::list<T>;
template<typename T> using Matrix = boost::numeric::ublas::matrix<T>;
template<typename T> using Shared = std::shared_ptr<T>;

using VectorInt = Vector<int>;
using MatrixCells = Matrix<CellType>;
using MonsterList = List<Shared<Monster>>;

template<typename T, typename U> auto makeItem(U& data) { return std::make_shared<T>(data); }	// сокращенный make_shared (с параметрами конструтора)
template<typename T> auto makeItem() { return std::make_shared<T>(); }							// сокращенный make_shared (без параметров конструтора)
