#pragma once

class BaseObject
{
public:

	BaseObject() { Init(); }
	~BaseObject() { Release(); }

	void Update();
	void Draw();

protected:

	void Release();
	void Init();

	KdTexture m_tex;
	Math::Vector3 m_pos = {};
	bool m_aliveFlg = true;

};

