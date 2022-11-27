#pragma once
#include <d2d1.h>
#include "IDrawable.h"
#include "Datastore.h"

class Brick : public IDrawable
{
	float opacity = 1.0f;
	const float TARG_BREAK_SCALE = 2.0f;
	float break_scale = 1.0f;
public:
	bool breaking = false;
	bool broken = false;
	float x;
	float y;
	float width;
	float height;
	Brick* prevb = NULL;
	Brick* nextb = NULL;
	D2D1_COLOR_F col;
	
	Brick() { }
	Brick(float x, float y) {
		this->x = x;
		this->y = y;
		this->width = Datastore::BRICK_WIDTH;
		this->height = Datastore::BRICK_HEIGHT;
	}
	Brick(float x, float y, float width, float height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
	~Brick() { }
	void Draw(ID2D1HwndRenderTarget* renderTarget);
	float left() { return x; }
	float right() { return x + width; }
	float top() { return y; }
	float bottom() { return y + height; }
	void Break();
	void Update();
};

