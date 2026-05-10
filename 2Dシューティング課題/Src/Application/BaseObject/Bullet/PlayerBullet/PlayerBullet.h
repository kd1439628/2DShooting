#pragma once
#include "../Bullet.h"

class PlayerBullet : public Bullet
{
public:
	PlayerBullet() { Init(); } // コンストラクタで自機弾用のInitを呼ぶ
private:
	void Init() override;
};