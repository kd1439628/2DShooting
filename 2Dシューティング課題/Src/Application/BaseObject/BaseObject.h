#pragma once

class BaseObject
{
public:

	BaseObject() {}
	virtual ~BaseObject() { Release(); }

	virtual void Update(std::vector<std::shared_ptr<BaseObject>>& objList);
	virtual void Draw();

	bool IsAlive()const { return m_aliveFlg; }

	const Math::Vector3& GetPos() const { return m_pos; }

	void SetPos(const Math::Vector3& pos) { m_pos = pos; }

	float GetRadius() const { return m_radius; }
	virtual void OnCollision() { m_aliveFlg = false; }

protected:

	virtual void Init();
	virtual void Release();

	KdTexture m_tex;
	Math::Vector3 m_pos;
	bool m_aliveFlg = true;
	float m_radius = 30.0f;
};

