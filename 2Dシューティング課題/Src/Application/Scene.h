#pragma once

class BaseScene;

class Scene
{
public:

	void Init();

	void Release();

	void Update();

	void Draw2D();

	void ImGuiUpdate();

	std::shared_ptr<BaseScene> m_nowScene;

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}

};

#define SCENE Scene::GetInstance()
