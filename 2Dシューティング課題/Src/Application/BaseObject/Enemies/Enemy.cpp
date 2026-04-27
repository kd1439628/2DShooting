#include "Enemy.h"

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Math::Rectangle rc;
	rc = { 0,0,64,64 };

	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_tex, m_pos.x, m_pos.y, 64, 64, &rc);
}

void Enemy::Init()
{
	m_tex.Load("Textures/enemy.png");
	m_pos = {};	// 0,0 で初期化
	m_aliveFlg = true;
}

void Enemy::Release()
{
}
