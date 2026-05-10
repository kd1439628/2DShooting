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

private:
	void Init();
	void Release();

	KdTexture m_hpTex;      // HPバー用画像
	KdTexture m_scoreTex;   // スコア用画像

	std::weak_ptr<Player> m_wpPlayer; // プレイヤーへの参照（循環参照防止のためweak_ptr）
	int m_lastDisplayHp = 4;
	const int BAR_W = 192; // 1コマあたりの横幅
	const int BAR_H = 80;  // 画像の縦幅
};