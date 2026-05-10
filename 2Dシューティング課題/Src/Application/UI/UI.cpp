#include "UI.h"
#include "../BaseObject/Player/Player.h"

void UI::Init()
{
	m_hpTex.Load("Textures/UI/Hp.png");
	m_lastDisplayHp = 4;
}

void UI::Update()
{
	// プレイヤーが生きている間（リストに存在している間）だけHPを更新
	if (auto player = m_wpPlayer.lock())
	{
		m_lastDisplayHp = player->GetHp();
	}
}

void UI::Draw()
{
	int maxHp = 4;

	// HPに応じた画像インデックスの計算
	int animeIdx = maxHp - m_lastDisplayHp;
	if (animeIdx < 0) animeIdx = 0;
	if (animeIdx > 4) animeIdx = 4;

	Math::Rectangle rc = { animeIdx * BAR_W, 0, BAR_W, BAR_H };

	// 画面左下に描画
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_hpTex, -550, -300, BAR_W, BAR_H, &rc
	);
}

void UI::Release()
{
}