#pragma once

class TitleStage
{
public:

	TitleStage() { Init(); }
	~TitleStage() { Release(); }

	void Update();
	void Draw();

private:

	void Init();
	void Release();

	// 背景画像
	KdTexture m_backTex;
	KdTexture m_decor1Tex;
	KdTexture m_decor2Tex;

	// スクロール用座標（Y軸）
	float m_backX = 0.0f;
	float m_decorX = 0.0f;

	// スクロール速度の定数
	const float BACK_SPEED = 4.0f;
	const float DECOR_SPEED = 4.0f;

	const int IMG_W = 1920;
	const int IMG_H = 1080;
};