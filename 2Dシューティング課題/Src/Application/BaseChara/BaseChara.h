#pragma once

class BaseChara
{
public:

	BaseChara() { Init(); }
	~BaseChara() { Release(); }

	void Update();
	void Draw();
	void Init();

protected:

	void Release();

	KdTexture m_tex;
	Math::Vector3 m_pos = {};
	bool m_aliveFlg = true;

};

