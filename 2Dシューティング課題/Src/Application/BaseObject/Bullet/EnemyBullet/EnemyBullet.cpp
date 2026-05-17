#include "EnemyBullet.h"

void EnemyBullet::Init()
{
	m_tex.Load("Textures/Bullet2.png"); // 敵弾のパス
	m_aliveFlg = true;
}
