#pragma once

//////////////////////////////////////////////////////////////////////////
// Константы
//////////////////////////////////////////////////////////////////////////

constexpr auto LevelWidth = 40;												// ширина уровня в тайлах
constexpr auto LevelHeigth = 40;											// высота уровня в тайлах
constexpr auto TileSize = 8;												// размер тайла

//////////////////////////////////////////////////////////////////////////
// Общие енумы
//////////////////////////////////////////////////////////////////////////

enum Direction																// направление движения
{
	Left, Right, Up, Down
};
