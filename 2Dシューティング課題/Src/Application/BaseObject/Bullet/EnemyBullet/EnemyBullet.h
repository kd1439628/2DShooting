#pragma once
#include "../Bullet.h"

class EnemyBullet : public Bullet
{
public:
	EnemyBullet() { Init(); } // コンストラクタで敵弾用のInitを呼ぶ
private:
	void Init() override;
};