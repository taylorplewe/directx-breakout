#include "Control.h"
#include "Ball.h"

void Control::Die() {
	fadingOut = true;
}

void Control::Restart() {
	ds->ball->Reposition();
	fadingIn = true;
	fadingOut = false;
}

void Control::Update() {
	if (!fadingIn && !fadingOut) return;
	if (fadingOut) {
		if (ds->overlayOpacity < 1.0f) ds->overlayOpacity += 0.05f;
		else fadingIn = true; // when both are true, signals main.cpp to recreate bricks
	}
	else {
		if (ds->overlayOpacity > 0.0f) ds->overlayOpacity -= 0.05f;
		else fadingIn = false;
	}
}