#pragma once

class BaseObject
{
public:

	BaseObject() { Init(); }
	virtual ~BaseObject() { Release(); }

	virtual void Update();
	virtual void Draw();

protected:

	virtual void Init();
	virtual void Release();

	KdTexture m_tex;
	Math::Vector3 m_pos = {};
	bool m_aliveFlg = true;

};

