#pragma once

class Player; // 相互参照を避けるための前方宣言

class UI
{
public:
	UI() { Init(); }
	~UI() { Release(); }

	void Update();
	void Draw();

	// 表示するためにプレイヤーの情報が必要な場合
	void SetPlayer(std::shared_ptr<Player> player) { m_wpPlayer = player; }

	void AddScore(int amount) {
		m_score += amount;
		// カンスト処理（999,999を超えない）
		if (m_score > 999999) {
			m_score = 999999;
		}
	}

	// 現在のスコアを取得する関数（必要であれば）
	unsigned long GetScore() const { return m_score; }

	void AddTime(int frame);

private:
	void Init();
	void Release();

	KdTexture m_hpTex;      // HPバー用画像
	KdTexture m_scoreTex;   // スコア用画像
	KdTexture m_scorefremeTex;
	KdTexture m_timeTex;
	KdTexture m_colonTex;

	std::weak_ptr<Player> m_wpPlayer; // プレイヤーへの参照（循環参照防止のためweak_ptr）
	int m_lastDisplayHp = 4;
	const int BAR_W = 240; // 1コマあたりの横幅
	const int BAR_H = 100;  // 画像の縦幅
	int m_score = 0;
	//扱う桁数の最大値
	static const int maxDigit = 6;
	int m_digit[maxDigit] = {};
	// 経過時間をカウントする変数
	int m_elapsedFrame = 0;
};