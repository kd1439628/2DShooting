#include "bullet.h"

void Bullet::Update()
{
	m_pos.x += 10.0f;

	if (m_pos.x > 640 + 16)
	{
		m_aliveFlg = false;
	}
}

void Bullet::Draw()
{
	Math::Rectangle rc = { 0, 0, 8, 8 };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_tex, m_pos.x, m_pos.y, 8, 8, &rc);
}

void Bullet::Init()
{
	m_tex.Load("Textures/bullet.png");
	m_pos = {};
	m_aliveFlg = true;
}

void Bullet::Release()
{

}
