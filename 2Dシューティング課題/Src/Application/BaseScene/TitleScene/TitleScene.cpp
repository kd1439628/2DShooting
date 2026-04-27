#include "TitleScene.h"
#include "../GameScene/GameScene.h"
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
	// 現在のキーの状態を取得
	bool currentReturnKey = (GetAsyncKeyState(VK_RETURN) & 0x8000);
	// 「前回は押されていなくて、今回は押されている」瞬間だけ遷移
	if (currentReturnKey && !m_prevReturnKey)
	{
		SceneManager::Instance().SetNextScene(std::make_shared<GameScene>());
	}
	// 今の状態を「次回のフレーム用の前回の状態」として保存
	m_prevReturnKey = currentReturnKey;
}

void TitleScene::Release()
{

}
