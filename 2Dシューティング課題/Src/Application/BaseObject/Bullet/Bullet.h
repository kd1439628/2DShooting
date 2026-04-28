#pragma once

#include "../BaseObject.h"

class Bullet :public BaseObject
{
public:

	Bullet() { Init(); }
	~Bullet() { Release(); }

	void Update();
	void Draw();

	void SetPos(const Math::Vector3& pos) { m_pos = pos; }

private:

	void Init();
	void Release();

};