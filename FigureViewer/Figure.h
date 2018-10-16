#ifndef FIGURE_H
#define FIGURE_H

#define WHITE RGB(255,255,255)
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
#define BLACK RGB(0,0,0)

class Figure
{
protected:
	int size;
	int offsetX, offsetY;
private:
	bool isDragging;
	bool controlIsPressed;
	int previousX, previousY;
	HDC dc;
	COLORREF color;
	void takeABrush(HDC dc, COLORREF c = WHITE)
	{
		HBRUSH br = CreateSolidBrush(c);
		SelectBrush(dc, br);
	}
public:
	Figure(int size, int offsetX, int offsetY) : size(size), offsetX(offsetX), offsetY(offsetY), isDragging(false), previousX(0), previousY(0), controlIsPressed(false)
	{
		setColor(BLUE);
	}
	void changeColor()
	{
		byte r = rand() % 256;
		byte g = rand() % 256;
		byte b = rand() % 256;
		setColor(RGB(r, g, b));
	}
	void Clear(HDC dc)//так как фигуру мы всегда сначала стираем а потом рисуем, то можно схитрить и устанавливать нужный цвет в HDC после выполнения clear
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		takeABrush(dc);
		Rectangle(dc, 0, 0, r.right, r.bottom);
		takeABrush(dc, color);
	}
	void setColor(COLORREF c)
	{
		color = c;
	}
	void setControl(bool flag)
	{
		controlIsPressed = flag;
	}
	virtual void Draw(HDC dc) = 0;
	virtual bool InnerPoint(int X, int Y) = 0;
	void MoveTo(int X, int Y)
	{
		offsetX = X;
		offsetY = Y;
	}
	void Move(int X, int Y)
	{
		offsetX += X;
		offsetY += Y;
	}
	void StartDragging(int X, int Y, HDC dc)
	{
		this->dc = dc;
		if(InnerPoint(X, Y))
			isDragging = true;
	}
	void Drag(int X, int Y)
	{
		MoveTo(X, Y);
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		if(offsetX + size > r.right)
		{
			offsetX = r.right - size;
		}
		if (offsetX - size < 0) {
			offsetX = 0 + size;
		}
		if (offsetY + size > r.bottom)
		{
			offsetY = r.bottom - size;
		}
		if (offsetY - size < 0)
		{
			offsetY = 0 + size;
		}
	}
	void StopDragging()
	{
		isDragging = false;
	}
	bool IsDragging()
	{
		return isDragging;
	}
	void Scale(int delta)
	{
		if (controlIsPressed)
			return;
		if (delta > 0)
			size++;
		else
			size = size - 1 > 0 ? size - 1 : 0;
	}
};

#endif FIGURE_H
