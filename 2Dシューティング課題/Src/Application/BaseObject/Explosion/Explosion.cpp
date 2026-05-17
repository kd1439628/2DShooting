#include "Explosion.h"

Explosion::Explosion(const Math::Vector3& pos)
{
	Init();
	m_pos = pos;
}

void Explosion::Init()
{
	m_tex.Load("Textures/UI/Explosion.png");
	m_aliveFlg = true;
	m_anime = 0.0f;
}

void Explosion::Update(std::vector<std::shared_ptr<BaseObject>>& objList)
{
	// アニメーションを進める
	m_anime += 0.3f;

	if (m_anime >= 8.0f)
	{
		m_anime = 0;
		m_aliveFlg = false;
	}
}

void Explosion::Draw()
{
	if (!m_aliveFlg) return;

	int animeIdx = (int)m_anime;

	Math::Rectangle rc;
	rc = { animeIdx * m_frameW, 0, m_frameW, m_frameH };

	// ★修正: 描画サイズも 180, 160 ではなく、実際のコマのサイズに合わせる
	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_tex, (int)m_pos.x, (int)m_pos.y, m_frameW, m_frameH, &rc
	);
}