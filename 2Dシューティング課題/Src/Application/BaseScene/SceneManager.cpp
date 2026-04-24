#include "SceneManager.h"

#include "GameScene/GameScene.h"
#include "TitleScene/TitleScene.h"

void SceneManager::PreUpdate()
{
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}
}

void SceneManager::Update()
{
	m_CurrentScene->Update();
}

void SceneManager::Draw()
{
	m_CurrentScene->Draw();
}

void SceneManager::Init()
{
	ChangeScene(m_currentSceneType);
}

void SceneManager::Release()
{

}

void SceneManager::ChangeScene(SceneType _SceneType)
{
	switch (_SceneType)
	{

	case SceneType::Title:
	{
		m_CurrentScene = std::make_shared<TitleScene>();
		break;
	}
	case SceneType::Game:
	{
		m_CurrentScene = std::make_shared<GameScene>();
		break;
	}

	}

	//②シーン管理を更新
	m_currentSceneType = _SceneType;
}

