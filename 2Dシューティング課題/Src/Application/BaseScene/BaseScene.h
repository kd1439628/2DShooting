#pragma once

class BaseScene
{
public:

	BaseScene()
	{
		m_prevReturnKey = (GetAsyncKeyState(VK_RETURN) & 0x8000);
		m_prevZKey = (GetAsyncKeyState('Z') & 0x8000);
		m_prevXKey = (GetAsyncKeyState('X') & 0x8000);
	}
	virtual ~BaseScene() {}

	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

protected:

	bool m_prevReturnKey = false;
	bool m_prevZKey = false;
	bool m_prevXKey = false;

};

