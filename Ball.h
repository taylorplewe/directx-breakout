#pragma once
#include <d2d1.h>
#include "IDrawable.h"
#include "Bat.h"
#include "Brick.h"
#include "Control.h"

class Datastore;
class Ball : public IDrawable
{
	Datastore* ds;

	float x;
	float y = 440.0f;
	const float r = 10.0f;

	float ySpeed = -8.0f;
	float xSpeed = 4.0f;

	float left() { return x - r; }
	float right() { return x - r; }
	float top() { return y - r; }
	float bottom() { return y + r; }

	D2D1_COLOR_F col = D2D1::ColorF(0.34f, 0.31f, 0.25f);

	void HitBricks();
public:
	bool held = true;
	int doneCounter = 100;

	Ball(Datastore* ds) {
		this->ds = ds;
		x = ds->carea.right / 2;
	}
	~Ball() {}
	void Draw(ID2D1HwndRenderTarget* renderTarget);
	void Update();
	void Reposition();
	void Go();
};

