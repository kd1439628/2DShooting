#include "Player.h"
#include "../Bullet/PlayerBullet/PlayerBullet.h"


void Player::Update(std::vector<std::shared_ptr<BaseObject>>& objList)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 10;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 10;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 10;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 10;
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

			m_firerateTimer = 20;
		}
	}

}

void Player::Init()
{
	m_tex.Load("Textures/player/ship01.png");
	m_pos = { -550,0 };
	m_aliveFlg = true;
	m_firerateTimer = 0;
	m_anime = 0;
	m_hp = 5;
	m_radius = 30.0f;
}

void Player::Draw()
{
	// 1. 現在のコマ番号（整数）を取得
	int animeIdx = (int)m_anime;

	// 2. 矩形（rc）の計算
	// 横に 128px ずつ並んでいるので、[コマ番号 × 128] が左端の座標になります
	Math::Rectangle rc;
	rc = { animeIdx * 180, 0, 180, 160 };

	// 3. 指定された形式で描画
	// プレイヤーの位置 (m_playerPos) に合わせてアニメーションを描画
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_tex, (int)m_pos.x, (int)m_pos.y, 180, 160, &rc);
}

void Player::Release()
{

}