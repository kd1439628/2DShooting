#include "GameoverScene.h"
#include "../SceneManager.h"
#include "../TitleScene/TitleScene.h"

GameoverScene::GameoverScene(unsigned long score, int surviveFrame, int damageCount)
{
	m_finalScore = score; // 受け取ったスコアを保存

	bool isClear = (surviveFrame >= 10920); // 3分完走したか
	int maxScore = 27600;                // Sランクに必要な目安スコア

	if (isClear) {
		if (score >= maxScore && damageCount == 0) {
			m_rankIndex = 0; // SS: 完走 ＋ フルスコア ＋ 被弾なし
		}
		else if (score >= maxScore && damageCount <= 5) {
			m_rankIndex = 1; // S: 完走 ＋ フルスコア + 被弾5回以内
		}
		else if (score >= maxScore) {
			m_rankIndex = 2; // A: 完走 ＋ フルスコア
		}
		else if (score >= maxScore * 0.7f) {
			m_rankIndex = 3; // B: 完走 ＋ スコア7割以上
		}
		else {
			m_rankIndex = 4; // C: 完走のみ（スコア7割未満）
		}
	}
	else {
		// 完走できなかった場合（2分未満などを含む）は一律でDランク
		m_rankIndex = 5;
	}

	Init();               // Initの中でスコアを桁分解する
}

void GameoverScene::Update()
{
	if (m_rankAlpha < 1.0f)
	{
		m_rankAlpha += 0.005f;

		if (m_rankAlpha > 1.0f) m_rankAlpha = 1.0f;
	}

	bool currentReturnState = (GetAsyncKeyState(VK_RETURN) & 0x8000);
	if (currentReturnState && !m_prevReturnKey)
	{
		SceneManager::Instance().SetNextScene(std::make_shared<TitleScene>());
	}
	m_prevReturnKey = currentReturnState;
}

void GameoverScene::Draw()
{
	Math::Color color = { 0.0f,0.0f,0.0f,1.0f };
	KdShaderManager::GetInstance().m_spriteShader.DrawBox(0, 0, 640, 360, &color, true);

	Math::Rectangle rc;
	rc = { 0, 0, 280, 45 };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_recordTex, 0, 250, 235, 45, &rc
	);

	Math::Rectangle frameRc;
	frameRc = { 0, 0, 500, 140 };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_frameTex, 0, 100, 500, 140, &frameRc
	);

	//スコア
	for (int i = 0; i < maxDigit; ++i)
	{
		//数字1つの画像サイズ
		Math::Rectangle ScoreRc = { 64 * m_digit[i],0,64,80 };

		float posX = -162;

		//桁別に表示
		KdShaderManager::GetInstance().m_spriteShader.DrawTex
		(
			&m_scoreTex,		//表示するテクスチャ
			posX + i * 64,		//x
			110,				//y
			64,					//幅
			80,					//高さ
			&ScoreRc					//切り取り場所を格納した変数
		);
	}

	Math::Rectangle rankRc = { 0, 0, 248, 200 };

	// 透明度を反映した色を作成
	Math::Color rankColor = { 1.0f, 1.0f, 1.0f, m_rankAlpha };

	// スコアの横など、適切な位置に描画
	// 引数の最後に &rankColor を渡すことでフェードインします
	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_rankTex[m_rankIndex],
		0, -100,           // 表示位置(x, y)
		248, 200,             // 表示サイズ
		&rankRc,            // 切り抜き範囲
		&rankColor          // ★ここがポイント！透明度を渡す
	);
}


void GameoverScene::Init()
{
	m_recordTex.Load("Textures/UI/Score222.png");
	m_frameTex.Load("Textures/UI/Table.png");
	m_scoreTex.Load("Textures/UI/Score111.png");

	m_rankTex[0].Load("Textures/UI/SS.png"); // SS
	m_rankTex[1].Load("Textures/UI/S.png");  // S
	m_rankTex[2].Load("Textures/UI/A.png");  // A
	m_rankTex[3].Load("Textures/UI/B.png");  // B
	m_rankTex[4].Load("Textures/UI/C.png");  // C
	m_rankTex[5].Load("Textures/UI/D.png");

	//受け取ったスコアを桁ごとに分解する
	unsigned long tmp = m_finalScore;
	for (int i = maxDigit - 1; i >= 0; --i)
	{
		m_digit[i] = tmp % 10;
		tmp /= 10;
	}
}

void GameoverScene::Release()
{

}
