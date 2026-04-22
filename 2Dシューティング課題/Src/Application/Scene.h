#pragma once

class Scene
{
public:

	void Init();

	void Release();

	void Update();

	void Draw2D();

	void ImGuiUpdate();

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
