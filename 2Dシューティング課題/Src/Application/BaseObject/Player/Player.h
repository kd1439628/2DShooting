#pragma once

#include "../BaseObject.h"

class Player :public BaseObject
{
public:

	Player() { Init(); }
	~Player() { Release(); }

	void Update();
	void Draw();

private:

	void Init();
	void Release();

	std::vector<std::shared_ptr<BaseObject>> m_bltList;

};

