#pragma once
#include "../BaseObject.h"

class Explosion : public BaseObject
{
public:
	Explosion(const Math::Vector3& pos);
	~Explosion() override {}

	void Update(std::vector<std::shared_ptr<BaseObject>>& objList) override;
	void Draw() override;

private:
	void Init() override;

	float m_anime = 0.0f;
	const int m_frameW = 200;      // 1600 / 8
	const int m_frameH = 131;      // 画像の高さ
	int animeIdx;
	char dbg;
};