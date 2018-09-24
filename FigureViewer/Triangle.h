#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Figure.h"

class Triangle : public Figure
{
public:
	Triangle(int size = 12, int offsetX = 100, int offsetY = 100) : Figure(size, offsetX, offsetY)
	{
	}
	void Draw(HDC dc)
	{
		Ellipse(dc, offsetX - size, offsetY - size, offsetX + size, offsetY + size);//отрисовка эллипса
		MoveToEx(dc, offsetX - size, offsetY, NULL);// перемещение в точку левого края эллипса
		LineTo(dc, offsetX + size, offsetY);//линия до правого края
		MoveToEx(dc, offsetX, offsetY - size, NULL);//перемещение в точку верхнего края эллипса посередине
		LineTo(dc, offsetX, offsetY + size);//линия до нижнего края
	}
	bool InnerPoint(int X, int Y)
	{
		return (X - offsetX)*(X - offsetX) + (Y - offsetY)*(Y - offsetY) <= size * size;//все точки что меньше - в круге, равны - НА окружности
	}
};

#endif TRIANGLE_H
