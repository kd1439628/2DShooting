#pragma once

#include "../BaseObject.h"
#include <SimpleMath.h>

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

	// ダメージ処理
	void OnDamage(int damage) {
		m_hp -= damage;
		if (m_hp <= 0) m_aliveFlg = false;
	}

	Type GetType() const { return m_type; }

	void InitializeAs(Type type, Math::Vector3 pos);

protected:

	void Init()override;
	void Release()override;

private:

	Type	m_type = Type::Normal;
	int		m_hp = 1;
	float	m_speed = 0;
	float	m_anime = 0;	// 画像の横のコマ数（10個）
	float m_hitAnime;
	int m_firerateTimer = 0;

	KdTexture m_HitTex;
};