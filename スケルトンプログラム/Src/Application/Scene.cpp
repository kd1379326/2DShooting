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
	JudgeChangeScene();

	// それぞれのシーン(ゲーム場面)の更新処理
	SCENEMANAGER.Update();

}

// 初期化内容はここに
void Scene::Init()
{
	// 取り出す数値をシャッフルする。
	srand(timeGetTime());

	// キーフラグは先にfalseにしておく
	M_ChangeSceneFlg = false;
	// 最初のシーン(ゲーム場面)を入れる
	M_NowScene = ME_MainGame;

	// 初めに持ってくるシーン(ゲーム場面)をここで選ぶ
	SCENEMANAGER.ChangeState(new C_MainGameScene());
	// それぞれのシーン(ゲーム場面)の初期化処理
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



// ゲームの場面切り替え(シーン遷移)を行うかここで判定する。
void Scene::JudgeChangeScene()
{
	// キーフラグでスペースキーが押されたときのみシーン遷移(ゲームの場面切り替え)を行う。
	// 現在のシーンを確認し、目的のシーンへ遷移させる。
	// スペースキーを押しているとフラグがtrueになって遷移処理を遮断、離すとフラグがfalseになって再度スペースキーで遷移できる	if (M_ChangeSceneFlg == false)。
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (M_ChangeSceneFlg == false)
		{
			switch (M_NowScene)
			{
				case ME_Title:
				{
					// SCENEMANAGERからシーンのクラスを作成。
					SCENEMANAGER.ChangeState(new C_MainGameScene());
					// シーンを切り替えるのでちゃんと初期化する
					SCENEMANAGER.Init();
					M_NowScene = ME_MainGame;
					M_ChangeSceneFlg = true;
					break;
				}
				case ME_MainGame:
				{
					// SCENEMANAGERからシーンのクラスを作成。
					SCENEMANAGER.ChangeState(new C_MainGameScene());
					// シーンを切り替えるのでちゃんと初期化する
					SCENEMANAGER.Init();
					M_NowScene = ME_MainGame;
					M_ChangeSceneFlg = true;
					break;
				}
				case ME_Result:
				{
					// SCENEMANAGERからシーンのクラスを作成。
					SCENEMANAGER.ChangeState(new C_TitleScene());
					// シーンを切り替えるのでちゃんと初期化する
					SCENEMANAGER.Init();
					M_NowScene = ME_Title;
					M_ChangeSceneFlg = true;
					break;
				}
				//default:
				//{
				//	PostQuitMessage(0);
				//	break;
				//}
			}
		}
	}
	else
	{
		M_ChangeSceneFlg = false;
	}
}