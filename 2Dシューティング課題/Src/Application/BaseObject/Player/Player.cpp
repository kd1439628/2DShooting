#include "Player.h"
#include "../Bullet/PlayerBullet/PlayerBullet.h"
#include "../Explosion/Explosion.h"

void Player::Update(std::vector<std::shared_ptr<BaseObject>>& objList)
{
	// Iキーで無敵モードのON/OFFを切り替える（デバッグ用）
	bool currentIKey = (GetAsyncKeyState('I') & 0x8000);
	// 今押されていて、かつ前のフレームで押されていなかった時だけ（1回押し判定）
	if (currentIKey && !m_prevIKey)
	{
		m_isInvincible = !m_isInvincible; // true/false を反転させる

		// 出力ウィンドウで状態を確認できるようにする
		if (m_isInvincible) OutputDebugStringA("【デバッグ】無敵モード: ON\n");
		else OutputDebugStringA("【デバッグ】無敵モード: OFF\n");
	}
	m_prevIKey = currentIKey; // 今のキー状態を保存して次フレームへ

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (m_pos.x < -320) m_pos.x -= 7;
		else if (m_pos.x < 0) m_pos.x -= 10;
		else m_pos.x -= 13;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_pos.x < -320) m_pos.x += 7;
		else if (m_pos.x < 0) m_pos.x += 10;
		else m_pos.x += 13;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (m_pos.x < -320) m_pos.y += 7;
		else if (m_pos.x < 0) m_pos.y += 10;
		else m_pos.y += 13;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (m_pos.x < -320) m_pos.y -= 7;
		else if (m_pos.x < 0) m_pos.y -= 10;
		else m_pos.y -= 13;
	}

	// 左右の制限（画面中央 0 から ±640 の場合）
	if (m_pos.x < -600) m_pos.x = -600; // 左端
	if (m_pos.x > 600) m_pos.x = 600; // 右端

	// 上下の制限（画面中央 0 から ±360 の場合）
	if (m_pos.y < -320) m_pos.y = -320; // 下端
	if (m_pos.y > 320) m_pos.y = 320; // 上端

	/////////////////////////////////////////////////
	//アニメーション                               //
	/////////////////////////////////////////////////
	m_anime += 0.2f;

	if (m_anime >= 10.0f)
	{
		m_anime = 0;
	}

	m_hitAnime += 0.2f;

	if (m_hitAnime >= 4.0f)
	{
		m_hitAnime = 0;
	}

	/////////////////////////////////////////////////
	//                    Bullet                   //
	/////////////////////////////////////////////////
	if (m_firerateTimer > 0) m_firerateTimer--;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_firerateTimer <= 0)
		{
			// 自機用の弾を作成
			auto bullet = std::make_shared<PlayerBullet>();

			// 弾の出現位置を自機の位置に設定
			Math::Vector3 spawnPos = m_pos;
			spawnPos.x += 90.0f;
			bullet->SetPos(spawnPos);

			// ★ 右方向へ発射
			bullet->SetMove({ 12.0f, 0, 0 });

			// リストに追加
			objList.push_back(bullet);

			if (m_pos.x < -320) m_firerateTimer = 20;
			else if (m_pos.x < 0) m_firerateTimer = 15;
			else m_firerateTimer = 10;
		}
	}
}

void Player::Init()
{
	m_tex.Load("Textures/player/ship01.png");
	m_HitTex.Load("Textures/UI/PHitbox.png");
	m_pos = { -550,0 };
	m_aliveFlg = true;
	m_firerateTimer = 0;
	m_anime = 0.0f;
	m_hitAnime = 0.0f;
	m_hp = 4;
	m_maxHp = 4;
	m_radius = 30.0f;
}

void Player::Draw()
{
	// 1. 現在のコマ番号（整数）を取得
	int animeIdx = (int)m_anime;
	int hitAnimeIdx = (int)m_hitAnime;

	// 2. 矩形（rc）の計算
	// 横に 128px ずつ並んでいるので、[コマ番号 × 128] が左端の座標になります
	Math::Rectangle rc;
	rc = { animeIdx * 180, 0, 180, 160 };

	// 3. 指定された形式で描画
	// プレイヤーの位置 (m_playerPos) に合わせてアニメーションを描画
	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_tex, (int)m_pos.x, (int)m_pos.y, 180, 160, &rc
	);

	Math::Rectangle HitRc;
	HitRc = { hitAnimeIdx * 80, 0, 80, 60 };

	// 3. 指定された形式で描画
	// プレイヤーの位置 (m_playerPos) に合わせてアニメーションを描画
	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_HitTex, (int)m_pos.x, (int)m_pos.y, 80, 60, &HitRc
	);
}

void Player::OnDamage(int damage)
{
	if (!m_aliveFlg) return;
	if (m_isInvincible) return;

	if (damage > 0) m_damageCount++;

	m_hp -= damage;
	if (m_hp <= 0)
	{
		m_hp = 0;
		m_aliveFlg = false;
	}
}

void Player::Release()
{

}