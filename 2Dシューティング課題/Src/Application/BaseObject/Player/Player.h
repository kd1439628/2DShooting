#pragma once

#include "../BaseObject.h"

class Player :public BaseObject
{
public:

	Player() { Init(); }
	~Player()override { Release(); }

	void Update(std::vector<std::shared_ptr<BaseObject>>& objList);
	void Draw()override;
	void OnDamage(int damage)
	{
		m_hp -= damage;
		if (m_hp <= 0) {
			m_hp = 0;
			m_aliveFlg = false; // HPが0になったら死亡
		}
	}
	int GetHp() const { return m_hp; }

private:

	void Init()override;
	void Release()override;

	int m_firerateTimer = 0;

	float m_anime = 0;

	int m_hp = 0;
};

