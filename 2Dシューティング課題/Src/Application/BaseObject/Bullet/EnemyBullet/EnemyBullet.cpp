#include "EnemyBullet.h"

void EnemyBullet::Init()
{
	m_tex.Load("Textures/EnemyBullet.png"); // 敵弾のパス
	m_aliveFlg = true;
}
