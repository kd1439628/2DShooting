#include "TitleScene.h"

#include "../SceneManager.h"

void TitleScene::Draw()
{
	KdShaderManager::GetInstance().m_spriteShader.DrawCircle(0, 0, 100);
}

void TitleScene::Init()
{

}

void TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::Release()
{

}
