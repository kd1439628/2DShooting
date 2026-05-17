#pragma once

#include "../BaseObject.h"
#include "../../UI/UI.h"

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

	void AddScore(int val) { m_score += val; if (m_score > 999999) m_score = 999999; }
	int GetScore() const { return m_score; }
	int GetDamageCount() const { return m_damageCount; }

	std::shared_ptr<UI> GetUI() const { return m_ui; }

private:

	void Init()override;
	void Release()override;

	int m_firerateTimer = 0;
	float m_anime = 0;
	float m_hitAnime;
	int m_hp = 5;
	int m_maxHp = 5;
	int m_score = 0;
	int m_damageCount = 0;

	KdTexture m_HitTex;

	std::shared_ptr<UI> m_ui = nullptr;

	//無敵デバックキー
	bool m_isInvincible = false; // 無敵状態かどうかのフラグ
	bool m_prevIKey = false;     // 前のフレームのIキーの状態（1回押し判定用）
};

