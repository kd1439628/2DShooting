#include "Stage.h"

void Stage::Init()
{
	m_backTex.Load("Textures/Stage/BG_1080x3000.png");
	m_decorTex.Load("Textures/Stage/Decor_A_1080x3000.png");

	m_backX = 0.0f;
	m_decorX = 0.0f;
}

void Stage::Update()
{
	// 下方向にスクロール
	m_backX -= BACK_SPEED;
	m_decorX -= DECOR_SPEED;

	// 画像の幅分移動したらループさせる
	if (m_backX <= -IMG_W) { m_backX += IMG_W; }
	if (m_decorX <= -IMG_W) { m_decorX += IMG_W; }
}

void Stage::Draw()
{
	Math::Rectangle rc = { 0, 0, (long)IMG_W, (long)IMG_H };

	// 2. 宣言した rc を使って描画する
	// --- 背景の描画 ---
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_backTex, (int)m_backX, 0, IMG_W, IMG_H, &rc);

	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_backTex, (int)m_backX + IMG_W, 0, IMG_W, IMG_H, &rc);


	// --- 装飾の描画 ---
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_decorTex, (int)m_decorX, 0, IMG_W, IMG_H, &rc);

	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_decorTex, (int)m_decorX + IMG_W, 0, IMG_W, IMG_H, &rc);
}

void Stage::Release()
{
}