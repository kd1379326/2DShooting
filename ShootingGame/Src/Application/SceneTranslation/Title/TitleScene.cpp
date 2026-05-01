#include "TitleScene.h"

// シーン遷移を行うクラス
#include "../SceneManager&State/SceneManager.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_TitleScene::C_TitleScene()
{
	M_Title.MS_Position = { 0, 0 };
	
}

// このクラスが削除された時に動かしたいものをここに(コンストラクタ)
C_TitleScene::~C_TitleScene()
{
	// 解放処理
	Release();
	
}

// 初期化内容はここに
void C_TitleScene::Init()
{

}

// 更新前に行いたい更新処理はここに書く。
void C_TitleScene::PreUpdate()
{
}

// 更新内容はここに
void C_TitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_MainGame); }
}

// 更新後に行いたい更新処理はここに書く。
void C_TitleScene::PostUpdate()
{
}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_TitleScene::DrawSprite()
{
	SHADER.m_spriteShader.DrawString(M_Title.MS_Position.x, M_Title.MS_Position.y, "Title", { 1.0f, 1.0f, 1.0f, 1.0f });
}

// デバッグ画面に出したい内容はここに
void C_TitleScene::ImGuiUpdate()
{

}

// 解放処理
void C_TitleScene::Release()
{

}