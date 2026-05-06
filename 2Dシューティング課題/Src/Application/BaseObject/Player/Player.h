#pragma once

#include "../BaseObject.h"

class Player :public BaseObject
{
public:

	Player() { Init(); }
	~Player() { Release(); }

	void Update(std::vector<std::shared_ptr<BaseObject>>& objList);
	void Draw();

private:

	void Init();
	void Release();

	int m_firerateTimer = 0;

	float m_anime = 0;
};

