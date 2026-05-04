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
	C_SceneManager::Instance().Draw();
}

// 更新内容はここに
void Scene::Update()
{
	// メインの更新前に行う更新処理
	C_SceneManager::Instance().PreUpdate();

	// それぞれのシーン(ゲーム場面)の更新処理
	C_SceneManager::Instance().Update();

	// メインの更新後に行う更新処理
	C_SceneManager::Instance().PostUpdate();

}

// 初期化内容はここに
void Scene::Init()
{
	// 取り出す数値をシャッフルする。
	srand(timeGetTime());

	C_SceneManager::Instance().Init();
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
		C_SceneManager::Instance().ImGuiUpdate();
	}
	ImGui::End();
}

