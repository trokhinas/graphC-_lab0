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
		Ellipse(dc, offsetX - size, offsetY - size, offsetX + size, offsetY + size);//��������� �������
		MoveToEx(dc, offsetX - size, offsetY, NULL);// ����������� � ����� ������ ���� �������
		LineTo(dc, offsetX + size, offsetY);//����� �� ������� ����
		MoveToEx(dc, offsetX, offsetY - size, NULL);//����������� � ����� �������� ���� ������� ����������
		LineTo(dc, offsetX, offsetY + size);//����� �� ������� ����
	}
	bool InnerPoint(int X, int Y)
	{
		return (X - offsetX)*(X - offsetX) + (Y - offsetY)*(Y - offsetY) <= size * size;//��� ����� ��� ������ - � �����, ����� - �� ����������
	}
};

#endif TRIANGLE_H
