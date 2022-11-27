#include <d2d1.h>
#include "d_boiler.h"

void d_boiler::CreateFactory() {
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)(&wFactory));
}

void d_boiler::OnPaint(HWND hwnd) {
	HRESULT res = CreateGraphicsResources(hwnd);
	if (SUCCEEDED(res)) {
		// start of Direct2D stuff
		pRenderTarget->BeginDraw();
		pRenderTarget->Clear(D2D1::ColorF(0.45f, 0.42f, 0.35f));

		// draw level indicator
		ID2D1SolidColorBrush* text_brush;
		pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.34f, 0.31f, 0.25f, 0.3f), &text_brush);
		D2D1_RECT_F text_rect = { 48, 0, 100, 100 };
		wchar_t level_text[2];
		wsprintf(level_text, L"%i", ds->level);
		pRenderTarget->DrawText(
			level_text,
			1,
			tFormat,
			text_rect,
			text_brush
		);

		// draw each object
		IDrawable* cd = ds->drawables[0];
		while (cd != NULL) {
			if (!cd->hidden) cd->Draw(pRenderTarget);
			cd = cd->next;
		}

		// fade overlay
		if (ds->overlayOpacity > 0) {
			ID2D1SolidColorBrush* fb;
			pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.45f, 0.42f, 0.35f, ds->overlayOpacity), &fb);
			pRenderTarget->FillRectangle(D2D1::RectF(0, 0, ds->carea.right, ds->carea.bottom), fb);
			fb->Release();
			fb = NULL;
		}

		res = pRenderTarget->EndDraw();
		if (FAILED(res) || res == D2DERR_RECREATE_TARGET) {
			DiscardGraphicsResources();
		}
	}
}

HRESULT d_boiler::CreateGraphicsResources(HWND hwnd) {
	HRESULT res = S_OK;

	// create text format
	res = wFactory->CreateTextFormat(
		L"Helvetica",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		200.0f,
		L"en-us",
		&tFormat
	);

	if (pRenderTarget == NULL) {
		RECT rc;
		GetClientRect(hwnd, &rc);

		// create Direct2D window render target
		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		res = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd, size),
			&pRenderTarget
		);
	}
	return res;
}

template <class T> void SafeRelease(T** ppT) {
	if (*ppT) {
		(*ppT)->Release();
		*ppT = NULL;
	}
}

void d_boiler::DiscardGraphicsResources() {
	SafeRelease(&pRenderTarget);
}