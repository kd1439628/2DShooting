#include "bullet.h"

void Bullet::Update(std::vector<std::shared_ptr<BaseObject>>& objList)
{
	m_pos += m_move;

	bool isOut = false;
	if (m_pos.x > 800)  isOut = true; // 右端
	if (m_pos.x < -800) isOut = true; // 左端
	if (m_pos.y > 500)  isOut = true; // 上端
	if (m_pos.y < -500) isOut = true; // 下端

	if (isOut)
	{
		m_aliveFlg = false; // これで死滅フラグが立つ
	}
}

void Bullet::Draw()
{
	Math::Rectangle rc = { 0, 0, 16, 16 };

	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_tex, (int)m_pos.x, (int)m_pos.y, 16, 16, &rc);
}

void Bullet::Init()
{
}

void Bullet::Release()
{
}
