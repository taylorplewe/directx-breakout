#pragma once
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#include <d2d1.h>
#include <dwrite.h>
#include "Datastore.h"
#include "IDrawable.h"

class d_boiler
{
	Datastore* ds;
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	IDWriteFactory* wFactory;
	IDWriteTextFormat* tFormat;

	HRESULT CreateGraphicsResources(HWND hwnd);
	void DiscardGraphicsResources();

public:
	d_boiler(Datastore* ds) { this->ds = ds; }
	~d_boiler() {}
	void OnPaint(HWND hwnd);
	void CreateFactory();
};

