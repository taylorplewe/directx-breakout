#include "IDrawable.h"

IDrawable::IDrawable() {
	this->prev = NULL;
	this->next = NULL;
}
IDrawable::~IDrawable() { }

void IDrawable::Draw(ID2D1HwndRenderTarget* renderTarget) { }