#pragma once

#include "../BaseObject.h"

class Enemy :public BaseObject
{
public:

	Enemy() { Init(); }
	~Enemy() { Release(); }

	void Update();
	void Draw();

private:

	void Init();
	void Release();

};