#include "Enemy.h"
#include <random>
#include "../Bullet/EnemyBullet/EnemyBullet.h"

// 指定した範囲のランダムな浮動小数点数を返す関数
float GetRandomFloat(float min, float max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(min, max);
	return dis(gen);
}

// 指定した範囲のランダムな整数を返す関数（タイプ判定用）
int GetRandomInt(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(min, max);
	return dis(gen);
}

void Enemy::Update(std::vector<std::shared_ptr<BaseObject>>& objList)
{
	// 左へ移動
	m_pos.x -= m_speed;

	// アニメーション更新
	m_anime += 0.2f;
	if (m_anime >= 10.0f) m_anime = 0;

	// 左端へ消えたら削除
	if (m_pos.x < -750.0f) m_aliveFlg = false;

	/////////////////////////////////////////////////
	//                    Bullet                   //
	/////////////////////////////////////////////////
	if (m_type != Type::Assault)
	{
		// 弾の発射タイマー
		if (m_firerateTimer > 0) m_firerateTimer--;

		// 画面内に入っている時だけ撃つ（x座標 640以内）
		if (m_pos.x < 640 && m_firerateTimer <= 0)
		{
			// 敵用の弾インスタンスを作成
			auto bullet = std::make_shared<EnemyBullet>();

			Math::Vector3 spawnPos = m_pos;
			spawnPos.x -= 40.0f;
			bullet->SetPos(spawnPos);

			if (m_type == Type::Normal) {
				bullet->SetMove({ -12.0f, 0, 0 });
				m_firerateTimer = 80;
			}
			else if (m_type == Type::Hard) {
				bullet->SetMove({ -12.0f, 0, 0 });
				m_firerateTimer = 120;
			}

			objList.push_back(bullet);
		}
	}
}

void Enemy::Draw()
{
	int frameW = 0;
	int frameH = 0;

	switch (m_type)
	{
	case Type::Assault:
		// 突撃タイプ（enemy1.png）の1コマのサイズ
		frameW = 192; // 仮の数値です。実際の画像の1コマの幅に合わせてください
		frameH = 74;
		break;

	case Type::Hard:
		frameW = 192;
		frameH = 159;
		break;
	case Type::Normal:
		frameW = 192;
		frameH = 150;
		break;
	}
	Math::Rectangle rc = { (int)m_anime * frameW, 0, frameW, frameH };

	// 描画（サイズ指定を切り替えた frameW, frameH に）
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_tex, (int)m_pos.x, (int)m_pos.y, frameW, frameH, &rc);
}

void Enemy::Relocate()
{
	float y = GetRandomFloat(-300.0f, 300.0f);
	m_pos = { 750.0f, y, 0.0f };
}

void Enemy::Init()
{
	m_aliveFlg = true;
	m_anime = 0;

	Relocate();

	int randType = GetRandomInt(1, 100);
	// Normal: 50% (1-50)
	// Hard: 25% (51-75)
	// Assault: 25% (76-100)

	if (randType <= 50) {
		// 【Normal】 雑魚敵 (50%)
		m_type = Type::Normal;
		m_hp = 2;
		m_speed = 4.0f;
		m_tex.Load("Textures/Enemy/enemy1.png");
	}
	else if (randType <= 75) {
		// 【Hard】 固い敵 (25%)
		m_type = Type::Hard;
		m_hp = 4;
		m_speed = 2.5f;
		m_tex.Load("Textures/Enemy/enemy2.png");
	}
	else {
		// 【Assault】 突撃 (25%)
		m_type = Type::Assault;
		m_hp = 2;
		m_speed = 16.0f;
		m_tex.Load("Textures/Enemy/enemy3.png");
	}
}

void Enemy::Release()
{
}
