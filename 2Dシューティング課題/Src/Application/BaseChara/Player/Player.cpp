#include "Player.h"

void Player::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 5;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 5;
	}
}

void Player::Init()
{
	m_tex.Load("Textures/player.png");
	m_pos = {};	// 0,0 Ç≈èâä˙âª
	m_aliveFlg = true;
}

void Player::Draw()
{
	KdShaderManager::GetInstance().m_spriteShader.DrawCircle(0, 0, 100);

	Math::Rectangle rc;
	rc = { 0,0,64,64 };

	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_tex, m_pos.x, m_pos.y, 64, 64, &rc);
}

void Player::Release()
{

}