#pragma once

#include "../BaseScene.h"

class GameoverScene :public BaseScene
{
public:

	GameoverScene(unsigned long score = 0, int surviveFrame = 0, int damageCount = 0);
	~GameoverScene() { Release(); }

	void Update()override;
	void Draw()override;

private:

	void Init()override;
	void Release()override;

	KdTexture m_recordTex;
	KdTexture m_scoreTex;
	KdTexture m_frameTex;

	KdTexture m_rankTex[6];
	int m_rankIndex = 5;

	float m_rankAlpha = 0.0f;

	//引き継いだスコアを保存する変数
	unsigned long m_finalScore = 0;

	// スコア表示用の各桁の配列（UIクラスと同様の仕組み）
	static const int maxDigit = 6;
	int m_digit[maxDigit] = {};
};

