#include "GameoverScene.h"
#include "../SceneManager.h"
#include "../TitleScene/TitleScene.h"

void GameoverScene::Update()
{
	bool currentReturnState = (GetAsyncKeyState(VK_RETURN) & 0x8000);
	if (currentReturnState && !m_prevReturnKey)
	{
		SceneManager::Instance().SetNextScene(std::make_shared<TitleScene>());
	}
	m_prevReturnKey = currentReturnState;
}

void GameoverScene::Draw()
{
	KdShaderManager::GetInstance().m_spriteShader.DrawBox(0, 0, 50, 50);
}

void GameoverScene::Init()
{

}

void GameoverScene::Release()
{

}
