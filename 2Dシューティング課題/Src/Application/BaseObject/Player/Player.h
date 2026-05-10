#pragma once

#include "../BaseObject.h"

class UI;

class Player :public BaseObject
{
public:

	Player() { Init(); }
	~Player()override { Release(); }

	void Update(std::vector<std::shared_ptr<BaseObject>>& objList);
	void Draw()override;

	void OnDamage(int damage);
	int GetHp() const { return m_hp; }
	int GetMaxHp() const { return m_maxHp; }

	//UIをセットする関数
	void SetUI(std::shared_ptr<UI> ui) { m_ui = ui; }

	void Heal(int amount)
	{
		m_hp += amount;
		if (m_hp > m_maxHp) m_hp = m_maxHp; // 最大値を超えないように制限
	}

private:

	void Init()override;
	void Release()override;

	int m_firerateTimer = 0;
	float m_anime = 0;
	int m_hp = 5;
	int m_maxHp = 5;

	std::shared_ptr<UI> m_ui = nullptr;
};

