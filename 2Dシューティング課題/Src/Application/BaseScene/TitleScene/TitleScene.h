#pragma once

#include "../BaseScene.h"

class TitleScene :public BaseScene
{
public:

	TitleScene() { Init(); }
	~TitleScene() { Release(); }

	void Update()override;
	void Draw()override;

private:

	void Init()override;
	void Release()override;

};