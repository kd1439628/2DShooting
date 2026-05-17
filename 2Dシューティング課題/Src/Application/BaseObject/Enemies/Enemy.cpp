#include "Enemy.h"
#include "../Bullet/EnemyBullet/EnemyBullet.h"

void Enemy::Update(std::vector<std::shared_ptr<BaseObject>>& objList)
{
	// 左へ移動
	m_pos.x -= m_speed;

	// アニメーション更新
	m_anime += 0.2f;
	if (m_anime >= 10.0f) m_anime = 0;

	m_hitAnime += 0.2f;

	if (m_hitAnime >= 4.0f)
	{
		m_hitAnime = 0;
	}

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
			if (m_type == Type::Normal) {
				// Normalタイプ：真ん中から1発だけ撃つ
				auto bullet = std::make_shared<EnemyBullet>();
				Math::Vector3 spawnPos = m_pos;
				spawnPos.x -= 40.0f;
				bullet->SetPos(spawnPos);
				bullet->SetMove({ -12.0f, 0, 0 });

				objList.push_back(bullet);
				m_firerateTimer = 80;
			}
			else if (m_type == Type::Hard) {
				// Hardタイプ：Y軸 +40 と -40 の位置から2発同時に撃つ

				// 1発目（上側）
				auto bullet1 = std::make_shared<EnemyBullet>();
				Math::Vector3 spawnPos1 = m_pos;
				spawnPos1.x -= 40.0f;
				spawnPos1.y += 40.0f;
				bullet1->SetPos(spawnPos1);
				bullet1->SetMove({ -12.0f, 0, 0 });
				objList.push_back(bullet1);

				// 2発目（下側）
				auto bullet2 = std::make_shared<EnemyBullet>();
				Math::Vector3 spawnPos2 = m_pos;
				spawnPos2.x -= 40.0f;
				spawnPos2.y -= 40.0f;
				bullet2->SetPos(spawnPos2);
				bullet2->SetMove({ -12.0f, 0, 0 });
				objList.push_back(bullet2);

				m_firerateTimer = 120;
			}
		}
	}
}

void Enemy::Draw()
{
	int hitAnimeIdx = (int)m_hitAnime;

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

	//ヒットボックス
	Math::Rectangle HitRc;
	HitRc = { hitAnimeIdx * 80, 0, 80, 60 };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_HitTex, (int)m_pos.x, (int)m_pos.y, 80, 60, &HitRc
	);
}

void Enemy::InitializeAs(Type type, Math::Vector3 pos)
{
	// マネージャーから渡された設計図通りのタイプと座標をセット
	m_type = type;
	m_pos = pos;

	// 生存フラグやアニメーションタイマーをリセット
	m_aliveFlg = true;
	m_anime = 0.0f;
	m_hitAnime = 0.0f;
	m_firerateTimer = 60; // 弾を撃つまでの初期クールタイム

	// ヒットボックスのコア画像を読み込み
	m_HitTex.Load("Textures/UI/EHitbox.png");

	// タイプに合わせてステータスと見た目を変更する
	if (m_type == Type::Normal) {
		m_hp = 2;
		m_speed = 4.0f;
		m_tex.Load("Textures/Enemy/enemy1.png");
	}
	else if (m_type == Type::Hard) {
		m_hp = 4;
		m_speed = 2.5f;
		m_tex.Load("Textures/Enemy/enemy2.png");
	}
	else if (m_type == Type::Assault) {
		m_hp = 1;
		m_speed = 16.0f;
		m_tex.Load("Textures/Enemy/enemy3.png");
	}
}

void Enemy::Init()
{
	m_aliveFlg = true;
	m_anime = 0;
	m_hitAnime = 0;
}

void Enemy::Release()
{
}
