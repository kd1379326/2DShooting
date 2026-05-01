// C_・・・クラス
// M_・・・メンバ
// A_・・・引数
// E_・・・列挙体
// S_・・・構造体
// P_・・・ポインター
// F_・・・フラグ

#include "main.h"
#include "Scene.h"
#include "SceneTranslation/SceneManager&State/SceneManager.h"

// 描画内容はここに
void Scene::Draw2D()
{
	// それぞれのシーン(ゲーム場面)の描画処理
	SCENEMANAGER.Draw();
}

// 更新内容はここに
void Scene::Update()
{
	// スペースキーでゲーム場面の切り替えを行う
	//JudgeChangeScene();

	SCENEMANAGER.PreUpdate();

	// それぞれのシーン(ゲーム場面)の更新処理
	SCENEMANAGER.Update();

}

// 初期化内容はここに
void Scene::Init()
{
	// 取り出す数値をシャッフルする。
	srand(timeGetTime());

	SCENEMANAGER.Init();
}

// 最後に解放したいものはここに
void Scene::Release()
{

}

// デバッグ画面に表示するものはここに
void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		SCENEMANAGER.ImGuiUpdate();
	}
	ImGui::End();
}

