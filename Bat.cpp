#include "Bat.h"
#include "Datastore.h"

void Bat::Draw(ID2D1HwndRenderTarget* renderTarget) {
	// create brush
	ID2D1SolidColorBrush* b;
	HRESULT res = renderTarget->CreateSolidColorBrush(col, &b);

	// draw rectangle at x
	D2D1_RECT_F rect = D2D1::RectF(x, y, x + width, y + height);
	D2D1_ROUNDED_RECT rrect = D2D1::RoundedRect(rect, 5, 5);
	renderTarget->FillRoundedRectangle(rrect, b);

	// release brush
	b->Release();
	b = NULL;
}

void Bat::Update(int x) {
	this->x = x - (width/2);
}