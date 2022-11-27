#include "Brick.h"

void Brick::Draw(ID2D1HwndRenderTarget* renderTarget) {
	// create brush
	ID2D1SolidColorBrush* b;
	col = D2D1::ColorF(0.34f, 0.31f, 0.25f, opacity);
	HRESULT res = renderTarget->CreateSolidColorBrush(col, &b);

	// transform for breaking anim
	D2D1_SIZE_F s = D2D1::SizeF(break_scale, break_scale);
	D2D1_POINT_2F p = D2D1::Point2F(x + width / 2, y + height / 2);
	renderTarget->SetTransform(D2D1::Matrix3x2F::Scale(s, p));

	// draw rectangle at x
	D2D1_RECT_F rect = D2D1::RectF(x, y, x + width, y + height);
	D2D1_ROUNDED_RECT rrect = D2D1::RoundedRect(rect, 5, 5);
	renderTarget->FillRoundedRectangle(rrect, b);
	
	// end matrix thing
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	// release brush
	b->Release();
	b = NULL;
}

void Brick::Break() {
	breaking = true;
	broken = true;
}

void Brick::Update() {
	if (!breaking) return;

	opacity -= 0.1f;
	const float scalediff = TARG_BREAK_SCALE - break_scale;
	break_scale += scalediff * 0.1;

	if (opacity <= 0) {
		hidden = true;
		breaking = false;
	}
}