#pragma once

#include "../BaseScene.h"

class ClearScene :public BaseScene
{
public:

	ClearScene() { Init(); }
	~ClearScene() { Release(); }

	void Update()override;
	void Draw()override;

private:

	void Init()override;
	void Release()override;
};

