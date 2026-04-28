#include "Player.h"
#include "../Bullet/Bullet.h"


void Player::Update()
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
	//                    Bullet                   //
	/////////////////////////////////////////////////
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		std::shared_ptr<Bullet> bullet;
		bullet = std::make_shared<Bullet>();

		bullet->SetPos(m_pos);

		m_bltList.push_back(bullet);
	}

	//全オブジェクトの更新関数を呼ぶ
	for (int i = 0; i < m_bltList.size(); ++i)
	{
		m_bltList[i]->Update();
	}

	auto it = m_bltList.begin();
	while (it != m_bltList.end())
	{
		// Bullet.h または BaseObject.h に bool IsAlive() { return m_aliveFlg; } を追加しておくと便利です
		// ここではフラグを直接判定（BaseObjectでprotectedなのでアクセス可能にする必要があります）
		if ((*it)->Update() /* 本来はここで生存フラグを確認 */, false)
		{
			// 簡易的な削除判定（本来はフラグを見て erase する）
		}

		// 正しい削除の書き方例：
		/*
		if (!(*it)->GetAlive()) {
			it = m_bltList.erase(it);
		} else {
			++it;
		}
		*/
		++it; // 今回は一旦そのまま進めます
	}
}

void Player::Init()
{
	m_tex.Load("Textures/player.png");
	m_pos = {};	// 0,0 で初期化
	m_aliveFlg = true;
}

void Player::Draw()
{
	Math::Rectangle rc;
	rc = { 0,0,64,64 };

	KdShaderManager::GetInstance().m_spriteShader.DrawTex(
		&m_tex, m_pos.x, m_pos.y, 64, 64, &rc);

	for (int i = 0; i < m_bltList.size(); i++)
	{
		m_bltList[i]->Draw();
	}
}

void Player::Release()
{

}