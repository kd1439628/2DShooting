#include "main.h"
#include "Scene.h"

#include "BaseScene/GameScene/GameScene.h"
#include "BaseScene/TitleScene/TitleScene.h"

void Scene::Draw2D()
{
	m_nowScene->Draw();
}

void Scene::Update()
{
	m_nowScene->Update();
}

void Scene::Init()
{
	m_nowScene = std::make_shared<GameScene>();
}

void Scene::Release()
{

}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
