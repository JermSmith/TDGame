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
T distanceBetweenPoints(T x1, T y1, T x2, T y2) // for points
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

template <typename T>
float distanceBetweenPoints(T v1, T v2) // for vector2f
{
	return (sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y)));
}

template <typename T>
bool bIsPrime(T input)
{
	int i = (int)round(input);
	bool bResult = true;

	if (i <= 1)
	{
		bResult = false; // the input is 1 (or 0), which is not prime
	}
	else
	{
		for (int n = 2; n <= i / 2; n++)
		{
			if (i % n == 0)
			{
				bResult = false; // has been found to be composite
			}
		}
	}
	
	return bResult;
}

