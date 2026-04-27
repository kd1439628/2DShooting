#pragma once

class BaseScene
{
public:

	BaseScene() { m_prevReturnKey = (GetAsyncKeyState(VK_RETURN) & 0x8000); }
	virtual ~BaseScene() {}

	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

protected:

	bool m_prevReturnKey = false;

};

