#pragma once

#include "../BaseObject.h"

class Bullet :public BaseObject
{
public:

	Bullet() { Init(); }
	~Bullet() override { Release(); }

	void Update(std::vector<std::shared_ptr<BaseObject>>& objList)override;
	void Draw()override;

	void SetPos(const Math::Vector3& pos) { m_pos = pos; }
	void SetMove(const Math::Vector3& move) { m_move = move; }

protected:

	void Init()override;
	void Release()override;

	Math::Vector3 m_move = { 0, 0, 0 };
};