#pragma once

constexpr float PI = 3.14159265f;
constexpr float MIN_PI = 3.14f;

namespace sizes
{
	constexpr unsigned int WORLD_SIZE_X = 1280;
	constexpr unsigned int WORLD_SIZE_Y = 720;

	constexpr unsigned int PLAYINGMENU_X = 320; //height of playing menu is world_size_y
}

template <typename T>
T toRadians(T degrees)
{
	return degrees * PI / 180;
}

template <typename T>
T toDegrees(T radians)
{
	return (radians * 180) / PI;
}

template <typename T>
T distanceBetweenPoints(T x1, T y1, T x2, T y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
