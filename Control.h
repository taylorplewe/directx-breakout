#pragma once
#include "Datastore.h"

class Control
{
	Datastore* ds;
public:
	bool fadingOut;
	bool fadingIn;

	Control(Datastore* ds) { this->ds = ds; }
	~Control() {}
	void Die();
	void Update();
	void Restart();
};

