#include "UI.h"
#include "../BaseObject/Player/Player.h"

void UI::AddTime(int frame)
{
	m_elapsedFrame += frame;
	if (m_elapsedFrame < 0) {
		m_elapsedFrame = 0;
	}
}

void UI::Init()
{
	m_hpTex.Load("Textures/UI/Hp.png");
	m_scoreTex.Load("Textures/UI/Score.png");
	m_scorefremeTex.Load("Textures/UI/Table.png");
	m_timeTex.Load("Textures/UI/Time.png");
	m_colonTex.Load("Textures/UI/Time1.png");

	m_lastDisplayHp = 4;
	m_score = 0;
	// 配列も 0 で初期化しておく
	for (int i = 0; i < maxDigit; ++i)
	{
		m_digit[i] = 0;
	}
}

void UI::Update()
{
	m_elapsedFrame++;

	// プレイヤーが生きている間（リストに存在している間）だけHPを更新
	if (auto player = m_wpPlayer.lock())
	{
		m_lastDisplayHp = player->GetHp();

		m_score = player->GetScore();
	}

	//配列に各桁の数値を格納
	unsigned long tmp = m_score;
	for (int i = maxDigit - 1; i >= 0; --i)
	{
		//下位の桁から抽出し配列に格納
		m_digit[i] = tmp % 10;
		tmp /= 10;
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
		&m_hpTex, -520, -300, BAR_W, BAR_H, &rc
	);

	//スコア表示
	for (int i = 0; i < maxDigit; ++i)
	{
		//数字1つの画像サイズ
		Math::Rectangle rc = { 40 * m_digit[i],0,40,50 };

		float posX = -590;

		//桁別に表示
		KdShaderManager::GetInstance().m_spriteShader.DrawTex
		(
			&m_scoreTex,		//表示するテクスチャ
			posX + i * 40,		//x
			300,				//y
			40,					//幅
			50,					//高さ
			&rc					//切り取り場所を格納した変数
		);
	}

	// =============== タイマー表示 ===============
	// 1. フレームを秒・分に変換
	// 1. 制限時間を設定（3分 = 180秒）して、経過秒数を引く
	int limitSeconds = 180;
	int totalSeconds = limitSeconds - (m_elapsedFrame / 60);

	// 0秒未満にならないように制限（00:00でストップさせる）
	if (totalSeconds < 0) totalSeconds = 0;

	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;

	// 2. 表示する4つの数字（分10の位、分1の位、秒10の位、秒1の位）を取り出す
	int m10 = (minutes / 10) % 10;
	int m1 = minutes % 10;
	int s10 = (seconds / 10) % 10;
	int s1 = seconds % 10;

	int timeDigits[4] = { m10, m1, s10, s1 };

	// 3. 右上の描画開始位置（※もし画面外にはみ出たら、450の部分を調整してください）
	float timeStartX = 450.0f;
	float timeY = 300.0f;

	float gapSize = 20.0f;

	for (int i = 0; i < 4; ++i)
	{
		Math::Rectangle rc = { 40 * timeDigits[i], 0, 40, 50 };

		float currentGap = 0.0f;
		if (i >= 2) currentGap = gapSize;

		KdShaderManager::GetInstance().m_spriteShader.DrawTex
		(
			&m_timeTex,
			timeStartX + (i * 40) + currentGap,
			timeY,
			40,
			50,
			&rc
		);
	}

	// コロン
	Math::Rectangle colonSrc = { 0, 0, 12, 40 };

	// 描画する位置を計算（分2つ分 80px ＋ 隙間の半分）
	float colonPosX = timeStartX + 80.0f + (gapSize / 2.0f);

	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_colonTex,
		(int)colonPosX - 20, // 位置の微調整
		(int)timeY,
		20, 50,          // 画面上の大きさ（幅20, 高さ50）
		&colonSrc
	);

}

void UI::Release()
{
}