#pragma once

#include "../BaseScene.h"
#include "../../Stage/TitleStage/TitleStage.h"

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

	std::shared_ptr<TitleStage> m_tStage = nullptr;
	KdTexture m_enterTex;
	KdTexture m_nameTex;
	KdTexture m_name2Tex;

	float m_alphaAdd = 0.01f;
	float m_alpha = 1.0f;

};