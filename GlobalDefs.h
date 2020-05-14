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
#include "QMetaType"

//////////////////////////////////////////////////////////////////////////
// Предварительные объявы
//////////////////////////////////////////////////////////////////////////
class Monster;
class Track;

//////////////////////////////////////////////////////////////////////////
// Константы
//////////////////////////////////////////////////////////////////////////

constexpr auto LevelWidth = 84;															// ширина уровня в тайлах
constexpr auto LevelHeigth = 52;														// высота уровня в тайлах
constexpr auto TileSize = 16;															// размер тайла
constexpr auto BorderSize = 2;															// размер начального бордюра
constexpr auto BorderSizeMonster = BorderSize + 1;										// размер начального бордюра для монстров
constexpr auto AinmationFps = 120;														// кадров в секунду
constexpr auto MonsterSpeed = 20;														// скорость монстра
constexpr auto PlayerSpeed = 20;														// скорость игрока
constexpr auto BadPos = -1;																// неверная позиция
constexpr QPoint BadItemPos = QPoint{ BadPos, BadPos };									// неверная позиция итема

//////////////////////////////////////////////////////////////////////////
// Общие енумы
//////////////////////////////////////////////////////////////////////////

enum PlayerDirection																	// направление движения игрока
{
	Stop, Left, Right, Up, Down
};

enum class CellType																		// содержимое ячейки
{
	Water,																				// пустая
	Land,																				// откушенная
	Track,																				// занятая, но не откушенная
	Temp																				// временная для расчета заливки
};

//////////////////////////////////////////////////////////////////////////
// Удобные юзинги
//////////////////////////////////////////////////////////////////////////

template<typename T> using Vector = std::vector<T>;
template<typename T> using List = std::list<T>;
template<typename T> using Matrix = boost::numeric::ublas::matrix<T>;
template<typename T> using Shared = std::shared_ptr<T>;

using VectorInt = Vector<int>;
using VectorPoint = Vector<QPoint>;
using MatrixCells = Matrix<CellType>;
using MonsterList = List<Shared<Monster>>;
using TrackList = List<Shared<Track>>;

//////////////////////////////////////////////////////////////////////////
// Общие шаблоны
//////////////////////////////////////////////////////////////////////////

template<typename T, typename U> auto makeItem(U& data) { return std::make_shared<T>(data); }	// сокращенный make_shared (с параметрами конструтора)
template<typename T> auto makeItem() { return std::make_shared<T>(); }							// сокращенный make_shared (без параметров конструтора)
template<typename T, typename U> using Unmap = std::unordered_map<T, U>;						// сокращенная мапа

