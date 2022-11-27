#include "Ball.h"

#include "Datastore.h"

void Ball::Draw(ID2D1HwndRenderTarget* renderTarget) {
	// create brush
	ID2D1SolidColorBrush* b;
	HRESULT res = renderTarget->CreateSolidColorBrush(col, &b);

	// draw ellipse at x, y with radius r
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(x, y), r, r);
	renderTarget->FillEllipse(ellipse, b);

	// release brush
	b->Release();
	b = NULL;
}

void Ball::Update() {
	if (doneCounter < 100) doneCounter--;
	if (held) {
		y = ds->bat->y - r;
		x = ds->bat->x + ds->bat->width / 2;
		return;
	}
	// drift to right?
	//xSpeed += 0.1f;
	
	// die
	if (top() > ds->carea.bottom + 250.0f) {
		ds->control->Die();
	}
	// bounce of right wall
	if (right() > ds->carea.right) {
		x = ds->carea.right - r;
		xSpeed = -xSpeed;
	}
	// bounce of left wall
	else if (left() < 0) {
		x = r;
		xSpeed = -xSpeed;
	}
	// bounce of top wall
	if (top() < 0) {
		y = r;
		ySpeed = -ySpeed;
	}
	// bounce of bat
	else if (
		bottom() > ds->bat->y
		&& top() < ds->bat->y + ds->bat->height
		&& right() > ds->bat->x
		&& left() < ds->bat->x + ds->bat->width
		) {
		y = ds->bat->y - r;
		ySpeed = -ySpeed;
		// set x speed based off where the ball hit
		const float force = 8.0f;
		const float dist = ds->bat->width / 2;
		const float center = ds->bat->x + dist;
		const float pt = x - center;
		xSpeed = (pt / dist) * force;
		const float absXSpeed = xSpeed > 0 ? xSpeed : -xSpeed;
		const float newYSpeed = -(force - absXSpeed);
		//ySpeed = newYSpeed > -1.5f ? -1.5f : newYSpeed;
	}
	else HitBricks();

	// update position
	x += xSpeed;
	y += ySpeed;
}

void Ball::HitBricks() {
	Brick* cb = ds->bricks[0];
	while (cb != NULL) {
		if (
			!cb->broken
			&& top() < cb->bottom()
			&& bottom() > cb->top()
			&& left() < cb->right()
			&& right() > cb->left()
			) {
			float spdRatio = 1.0f;
			float posRatio = 1.0f;
			// d r
			if (ySpeed > 0 && xSpeed > 0) {
				spdRatio = ySpeed / xSpeed;
				posRatio = (right() - cb->left()) / (bottom() - cb->top());
			}
			// d l
			else if (ySpeed > 0 && xSpeed < 0) {
				spdRatio = ySpeed / -xSpeed;
				posRatio = (cb->right() - left()) / (bottom() - cb->top());
			}
			// u r
			else if (ySpeed < 0 && xSpeed > 0) {
				spdRatio = -ySpeed / xSpeed;
				posRatio = (right() - cb->left()) / (cb->bottom() - top());
			}
			// u l
			else if (ySpeed < 0 && xSpeed < 0) {
				spdRatio = -ySpeed / -xSpeed;
				posRatio = (cb->right() - left()) / (cb->bottom() - top());
			}
			if (spdRatio * posRatio > 1) ySpeed = -ySpeed;
			else xSpeed = -xSpeed;

			// destroy brick
			//cb->hidden = true;
			cb->Break();
			ds->numBricks--;
			if (ds->numBricks == 0) doneCounter--;

			break;
		}
		else cb = cb->nextb;
	}
}

void Ball::Reposition() {
	x = ds->carea.right / 2;
	y = 440.0f;
	xSpeed = 0;
	ySpeed = 0;
	held = true;
	doneCounter = 100;
}

void Ball::Go() {
	held = false;
	xSpeed = 4.0f;
	ySpeed = -8.0f;
}