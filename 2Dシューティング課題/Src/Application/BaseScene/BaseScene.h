#pragma once

class BaseScene
{
public:

	BaseScene() {}
	virtual ~BaseScene() {}

	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

private:



};

