#include "ClearScene.h"
#include "../SceneManager.h"
#include "../TitleScene/TitleScene.h"

void ClearScene::Update()
{
	bool currentReturnState = (GetAsyncKeyState(VK_RETURN) & 0x8000);
	if (currentReturnState && !m_prevReturnKey)
	{
		SceneManager::Instance().SetNextScene(std::make_shared<TitleScene>());
	}
	m_prevReturnKey = currentReturnState;
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
