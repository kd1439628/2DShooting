#pragma once

class BaseScene;

class SceneManager
{
public:

	void PreUpdate();
	void Update();
	void Draw();

	void SetNextScene(std::shared_ptr<BaseScene> _nextScene)
	{
		m_nextScene = _nextScene;
	}

private:

	void Init();
	void Release();
	void ChangeScene(std::shared_ptr<BaseScene> _nextScene);

	std::shared_ptr<BaseScene> m_currentScene;
	std::shared_ptr<BaseScene> m_nextScene;

private:

	SceneManager() { Init(); }
	~SceneManager() { Release(); }

public:
	static SceneManager& Instance()
	{
		static SceneManager Instance;
		return Instance;
	}
};