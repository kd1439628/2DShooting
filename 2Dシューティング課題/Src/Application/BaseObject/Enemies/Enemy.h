#pragma once

#include "../BaseObject.h"

class Enemy :public BaseObject
{
public:

	enum class Type {
		Normal,     // 雑魚
		Hard,       // 固い
		Assault     // 突撃
	};

	Enemy() { Init(); }
	~Enemy() override { Release(); }

	void Update(std::vector<std::shared_ptr<BaseObject>>& objList)override;
	void Draw()override;
	void Relocate();

	// ダメージ処理
	void OnDamage(int damage) {
		m_hp -= damage;
		if (m_hp <= 0) m_aliveFlg = false;
	}

	Type GetType() const { return m_type; }

protected:

	void Init()override;
	void Release()override;

private:

	Type	m_type = Type::Normal;
	int		m_hp = 1;
	float	m_speed = 0;

	float	m_anime = 0;	// 画像の横のコマ数（10個）

	int m_firerateTimer = 0;

};