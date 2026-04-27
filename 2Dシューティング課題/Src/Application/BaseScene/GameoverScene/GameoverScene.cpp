#include "GameoverScene.h"
#include "../SceneManager.h"
#include "../TitleScene/TitleScene.h"

void GameoverScene::Update()
{
	bool currentReturnState = (GetAsyncKeyState(VK_RETURN) & 0x8000);

	// 「前回は押されていなくて、今回は押されている」時だけ実行
	if (currentReturnState && !m_prevReturnKey)
	{
		SceneManager::Instance().SetNextScene(std::make_shared<TitleScene>());
	}

	// 次のフレームのために現在の状態を保存
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
