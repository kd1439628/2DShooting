#include "ClearScene.h"
#include "../SceneManager.h"
#include "../TitleScene/TitleScene.h"

void ClearScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!GetAsyncKeyState(VK_RETURN & 0x8000))
		{
			SceneManager::Instance().SetNextScene(std::make_shared<TitleScene>());
		}
	}
}

void ClearScene::Draw()
{
	KdShaderManager::GetInstance().m_spriteShader.DrawPoint(0, 0, (1, 1, 1, 0));
}

void ClearScene::Init()
{

}

void ClearScene::Release()
{

}
