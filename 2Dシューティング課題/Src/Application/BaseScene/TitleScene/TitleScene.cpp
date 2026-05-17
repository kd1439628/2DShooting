#include "TitleScene.h"
#include "../GameScene/GameScene.h"
#include "../SceneManager.h"
#include "../../Stage/TitleStage/TitleStage.h"

void TitleScene::Draw()
{
	Math::Color color = { 0.0f,0.0f,0.0f,1.0f };
	KdShaderManager::GetInstance().m_spriteShader.DrawBox(0, 0, 640, 360, &color, true);

	if (m_tStage) { m_tStage->Draw(); }

	Math::Rectangle nameRc = { 0, 0, 700, 180 };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_nameTex, 0, 100, 700, 180, &nameRc
	);

	Math::Rectangle name2Rc = { 0, 0, 800, 104 };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_name2Tex, 10, 50, 800, 104, &name2Rc
	);

	Math::Rectangle rc = { 0, 0, 500, 140 };
	Math::Color enterColor = { 1.0f,1.0f,1.0f,m_alpha };
	KdShaderManager::GetInstance().m_spriteShader.DrawTex
	(
		&m_enterTex, 0, -180, 500, 140, &rc, &enterColor
	);
}

void TitleScene::Init()
{
	m_enterTex.Load("Textures/UI/Enter.png");
	m_nameTex.Load("Textures/UI/Title.png");
	m_name2Tex.Load("Textures/UI/Explosion_3.png");
	m_tStage = std::make_shared<TitleStage>();
}

void TitleScene::Update()
{
	if (m_tStage) { m_tStage->Update(); }

	m_alpha += m_alphaAdd;

	if (m_alpha > 1.0f)
	{
		m_alpha = 1.0f;
		m_alphaAdd *= -1;
	}
	else if (m_alpha < 0.4f)
	{
		m_alpha = 0.4f;
		m_alphaAdd *= -1;
	}

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
