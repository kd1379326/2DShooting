#include "ResultScene.h"

// シーン遷移を行うクラス
#include "../SceneManager&State/SceneManager.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_ResultScene::C_ResultScene()
{
	M_Result.MS_Position = { 0, 0 };
	// シーン遷移させないようフラグを立てる。
	MF_Stop_ContinuitySceneTransition = true;

}

// このクラスが作成された時に動かしたいものをここに(コンストラクタ)
C_ResultScene::~C_ResultScene()
{
	// 解放処理
	Release();

}

// 初期化内容はここに
void C_ResultScene::Init()
{

}

// 更新前に行いたい更新処理はここに書く。
void C_ResultScene::PreUpdate()
{

}

// 更新内容はここに
void C_ResultScene::Update()
{
	// 遷移後、ENTER押し続けた判定でこのシーンを飛ばされないようにキーを離すまでシーン遷移許可を出さない。
	if (!(GetAsyncKeyState(VK_RETURN) & 0x8000)) { MF_Stop_ContinuitySceneTransition = false; }
	// 条件１：ENTERキーが押された
	// 条件２：シーン遷移のストッパーが外れている
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && (!MF_Stop_ContinuitySceneTransition)) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_Title); }
}

// 更新後に行いたい更新処理はここに書く。
void C_ResultScene::PostUpdate()
{

}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_ResultScene::DrawSprite()
{
	SHADER.m_spriteShader.DrawString(M_Result.MS_Position.x, M_Result.MS_Position.y, "Result", { 1.0f, 1.0f, 1.0f, 1.0f });
}

// デバッグ画面に出したい内容はここに
void C_ResultScene::ImGuiUpdate()
{

}

// 解放処理
void C_ResultScene::Release()
{

}