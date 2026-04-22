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

	int test = 0;
	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
