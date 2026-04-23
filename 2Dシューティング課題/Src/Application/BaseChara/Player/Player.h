#pragma once

#include "../BaseChara.h"

class Player :public BaseChara
{
public:

	Player() {}
	~Player() { Release(); }

	void Update();
	void Draw();
	void Init();

private:

	void Release();

};

