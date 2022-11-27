#include <windows.h>
#include <iostream>

#include "Datastore.h"
#include "IDrawable.h"
#include "w_boiler.h"
#include "d_boiler.h"
#include "Ball.h"
#include "Bat.h"
#include "Brick.h"
#include "Control.h"

Datastore* ds;

void CreateBricks();
void ClearBricks();
void Level1();
void Level2();
void Level3();
void Level4();
void CreateBrick(int* b, int* d, float x, float y, float width = 0.0f, float height = 0.0f) {
	Brick* br;
	if (!width && !height)
		br = new Brick(x, y);
	else
		br = new Brick(x, y, width, height);
	ds->bricks[*b] = br;
	ds->drawables[*d] = br;
	if (*b > 0) {
		ds->bricks[*b - 1]->nextb = br;
		br->prevb = ds->bricks[*b - 1];
	}
	ds->drawables[*d - 1]->next = br;
	br->prev = ds->drawables[*d - 1];
	(*b)++;
	(*d)++;
	ds->numBricks++;
}
LRESULT CALLBACK WindowProc(
	HWND hwnd,
	unsigned int uMsg,
	WPARAM wParam,
	LPARAM lParam
);
int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow
) {
	// init ds
	ds = new Datastore();
	ds->drawables = new IDrawable*[128];
	ds->w = new w_boiler(ds);
	ds->d = new d_boiler(ds);

	// init boilerplate stuff
	ds->w->CreateAndShowMainWindow(hInstance, nCmdShow, WindowProc);
	ShowCursor(0);

	// init objects
	GetClientRect(ds->m_hwnd, &ds->carea);
	ds->control = new Control(ds);
	ds->bat = new Bat(ds);
	ds->ball = new Ball(ds);
	ds->drawables[0] = ds->bat;
	ds->drawables[1] = ds->ball;
	ds->bat->next = ds->ball;

	CreateBricks();

	// TODO: set all prev's of drawables and bricks

	// Run message loop
	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);
		}
		else {
			ds->ball->Update();
			if (ds->ball->doneCounter == 0) ds->control->Die();
			ds->control->Update();
			if (ds->control->fadingIn && ds->control->fadingOut) {
				ClearBricks();
				if (ds->ball->doneCounter <= 0) {
					ds->level++;
					if (ds->level > 4) ds->level = 1;
				}
				CreateBricks();
				ds->control->Restart();
			}
			Brick* b = ds->bricks[0];
			while (b != NULL) {
				if (b->breaking) b->Update();
				b = b->nextb;
			}
			// Force program to paint constantly
			InvalidateRect(ds->m_hwnd, NULL, 0);
		}
	}

	return 0;
}

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	unsigned int uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (uMsg) {
	case WM_CREATE:
		ds->d->CreateFactory();
		return 0;
	case WM_DESTROY:
		// End of program
		ClearBricks();
		delete ds;
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		ds->bat->Update(lParam & 0xffff);
		return 0;
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);

		ds->d->OnPaint(hwnd);

		EndPaint(hwnd, &ps);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			// End of program
			ClearBricks();
			delete ds;
			PostQuitMessage(0);
		}
		return 0;
	case WM_LBUTTONDOWN:
		if (ds->ball->held) ds->ball->Go();
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void CreateBricks() {
	ds->numBricks = 0;
	ds->bricks = new Brick * [96];
	switch (ds->level) {
	case 1:
		Level1();
		break;
	case 2:
		Level2();
		break;
	case 3:
		Level3();
		break;
	case 4:
		Level4();
		break;
	}
}

void ClearBricks() {
	Brick* b = ds->bricks[0];
	while (b != NULL) {
		Brick* nextb = b->nextb;
		delete b;
		b = nextb;
		ds->drawables[1]->next = NULL;
	}
}

void Level1() {
	int b = 0;
	int d = 2;
	const char numRows = 8;
	const char numCols = 2;
	const float left = (ds->carea.right - 500) / 2;
	for (char r = 0; r < numRows; r++)
		for (char c = 0; c < numCols; c++)
			CreateBrick(&b, &d, left + c * 260, 20 + (40 * r), 240, 20);
}
void Level2() {
	int b = 0;
	int d = 2;
	const int numCols = 10;
	const float left = (ds->carea.right - 470.0f) / 2;
	for (char c = 0; c < numCols; c++)
		CreateBrick(&b, &d, left + (c * 50), 20.0f, 20.0f, 260.0f);
}
void Level3() {
	int b = 0;
	int d = 2;
	const int numCols = 6;
	const int numRows = 4;
	const float left = (ds->carea.right - 460.0f) / 2;
	for (int r = 0; r < numRows; r++)
		for (int c = 0; c < numCols; c++)
			CreateBrick(&b, &d, left + (80 * c), 20 + (80 * r), 60, 60);
}
void Level4() {
	int b = 0;
	int d = 2;
	const int numCols = 7;
	const int numRows = 8;
	const float left =
		(ds->carea.right -
			(
				(numCols * Datastore::BRICK_WIDTH) +
				((numCols - 1) * Datastore::BRICK_MARGIN)
				)
			) / 2;
	for (int r = 0; r < numRows; r++)
		for (int c = 0; c < numCols; c++)
			CreateBrick(&b, &d, left + (100 * c), 20 + (40 * r));
}