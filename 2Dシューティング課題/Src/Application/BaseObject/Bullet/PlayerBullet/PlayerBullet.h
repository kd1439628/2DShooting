#pragma once
#include "../Bullet.h"

class PlayerBullet : public Bullet
{
public:

	PlayerBullet() { Init(); }

	void Update(std::vector<std::shared_ptr<BaseObject>>& objList) override;

private:

	void Init() override;

};