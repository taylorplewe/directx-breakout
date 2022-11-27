#pragma once
#include <d2d1.h>

class IDrawable
{
public:
	IDrawable* prev;
	IDrawable* next;
	bool hidden = false;

	IDrawable();
	~IDrawable();
	virtual void Draw(ID2D1HwndRenderTarget* renderTarget);
};

