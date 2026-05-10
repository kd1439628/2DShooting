#pragma once

class UI
{
public:
	UI() {}
	~UI() {}



private:
	KdTexture m_texHp;
	int m_healScoreThreshold = 0; // 1000点数えるための蓄積変数
};