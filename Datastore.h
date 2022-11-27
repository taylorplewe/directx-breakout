#pragma once
#pragma comment(lib, "d2d1")

#include <windows.h>
#include <d2d1.h>

// forward definitions
class IDrawable;
class w_boiler;
class d_boiler;
class Bat;
class Ball;
class Brick;
class Control;

class Datastore
{
public:
	static constexpr SIZE WINDOW_SIZE = { 800, 600 };
	static constexpr float BRICK_WIDTH = 80.0f;
	static constexpr float BRICK_HEIGHT = 20.0f;
	static constexpr float BRICK_MARGIN = 20.0f;
	static constexpr float BAT_WIDTH = 100.0f;
	static constexpr float BAT_HEIGHT = 20.0f;
	HWND m_hwnd;
	w_boiler* w;
	d_boiler* d;
	IDrawable** drawables;
	Bat* bat;
	Ball* ball;
	Brick** bricks;
	RECT carea;
	Control* control;
	float overlayOpacity = 0.0f;
	char level = 1;
	char numBricks = 0;

	Datastore() {}
	~Datastore() {
		delete[] drawables;
		delete[] bricks;
		delete w;
		delete d;
		delete bat;
		delete ball;
	}
};

