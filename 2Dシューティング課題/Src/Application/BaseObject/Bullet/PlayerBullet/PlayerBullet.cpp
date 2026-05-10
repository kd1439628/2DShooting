#include "PlayerBullet.h"

void PlayerBullet::Init()
{
	m_tex.Load("Textures/bullet.png"); // 自機弾のパス
	m_aliveFlg = true;
}
