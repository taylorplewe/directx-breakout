#pragma once
#include <d2d1.h>
#include "IDrawable.h"
#include "Datastore.h"

class Bat : public IDrawable
{
	Datastore* ds;
	D2D1_COLOR_F col = D2D1::ColorF(0.34f, 0.31f, 0.25f);
public:
	Bat(Datastore* ds) { this->ds = ds; };
	~Bat() {};
	void Draw(ID2D1HwndRenderTarget* renderTarget);
	void Update(int x);

	const float y = 450.0f;
	float x = 10.0f;
	float width = Datastore::BAT_WIDTH;
	const float height = Datastore::BAT_HEIGHT;
};

