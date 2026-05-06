#include "Player.h"
#include "../Bullet/Bullet.h"


void Player::Update(std::vector<std::shared_ptr<BaseObject>>& objList)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 5;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 5;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_pos.y += 5;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pos.y -= 5;
	}

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
	if (m_firerateTimer > 0)
	{
		m_firerateTimer--;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_firerateTimer <= 0)
		{
			std::shared_ptr<Bullet> bullet;
			bullet = std::make_shared<Bullet>();

			bullet->SetPos(m_pos);

			objList.push_back(bullet);

			m_firerateTimer = 10;
		}
	}

}

void Player::Init()
{
	m_tex.Load("Textures/ship01.png");
	m_pos = {};	// 0,0 で初期化
	m_aliveFlg = true;
	m_firerateTimer = 0;
	m_anime = 0;
}

void Player::Draw()
{
	// 1. 現在のコマ番号（整数）を取得
	int animeIdx = (int)m_anime;

	// 2. 矩形（rc）の計算
	// 横に 128px ずつ並んでいるので、[コマ番号 × 128] が左端の座標になります
	Math::Rectangle rc;
	rc = { animeIdx * 256, 0, 256, 228 };

	// 3. 指定された形式で描画
	// プレイヤーの位置 (m_playerPos) に合わせてアニメーションを描画
	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_tex, (int)m_pos.x, (int)m_pos.y, 128, 114, &rc);
}

void Player::Release()
{

}