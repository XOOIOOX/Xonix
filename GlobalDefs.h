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

//////////////////////////////////////////////////////////////////////////
// Константы
//////////////////////////////////////////////////////////////////////////

constexpr auto LevelWidth = 40;												// ширина уровня в тайлах
constexpr auto LevelHeigth = 40;											// высота уровня в тайлах
constexpr auto TileSize = 8;												// размер тайла
constexpr auto BorderSize = 4;												// размер начального бордюра

//////////////////////////////////////////////////////////////////////////
// Общие енумы
//////////////////////////////////////////////////////////////////////////

enum Direction																// направление движения
{
	Left, Right, Up, Down
};

enum CellType																// содержимое ячейки
{
	Empty,																	// пустая
	Full,																	// откушенная
	Temp																	// занятая, но не откушенная
};

template<typename T> using Vector = std::vector<T>;
template<typename T> using List = std::list<T>;
template<typename T> using Matrix = boost::numeric::ublas::matrix<T>;
template<typename T> using Shared = std::shared_ptr<T>;

using VectorInt = Vector<double>;
using MatrixCells = Matrix<CellType>;
