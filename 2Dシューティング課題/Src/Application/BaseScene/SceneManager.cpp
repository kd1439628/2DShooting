#include "SceneManager.h"

#include "BaseScene.h"

void SceneManager::PreUpdate()
{
	if (m_nextScene)
	{
		ChangeScene(m_nextScene);
		m_nextScene = nullptr;
	}
}

void SceneManager::Update()
{
	if (m_currentScene)
	{
		m_currentScene->Update();
	}
}

void SceneManager::Draw()
{
	if (m_currentScene)
	{
		m_currentScene->Draw();
	}
}

void SceneManager::Init()
{
	m_currentScene = nullptr;
	m_nextScene = nullptr;
}

void SceneManager::Release()
{

}

void SceneManager::ChangeScene(std::shared_ptr<BaseScene> _nextScene)
{
	// 現在のシーンがあれば解放処理
	if (m_currentScene)
	{
		m_currentScene->Release();
	}

	// ステートの差し替え
	m_currentScene = _nextScene;

	// 新しいシーンの初期化
	if (m_currentScene)
	{
		m_currentScene->Init();
	}
}

