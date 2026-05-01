#include "GameOverScene.h"

// シーン遷移を行うクラス
#include "../SceneManager&State/SceneManager.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_GameOverScene::C_GameOverScene()
{

}

// このクラスが削除された時に動かしたいものをここに(コンストラクタ)
C_GameOverScene::~C_GameOverScene()
{
	// 解放処理
	Release();
}

// 初期化はここで行う。
void C_GameOverScene::Init()
{
	M_GameOver.MS_Position = { 0, 0 };
}

// 更新前に行いたい更新処理はここに書く。
void C_GameOverScene::PreUpdate()
{
}

// 更新処理はここに書く。
void C_GameOverScene::Update()
{
	if (GetAsyncKeyState('C') & 0x8000) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_Title); }
}

// 更新後に行いたい更新処理はここに書く。
void C_GameOverScene::PostUpdate()
{
}

// 描画処理はここに書く。
void C_GameOverScene::DrawSprite()
{
	KdShaderManager::GetInstance().m_spriteShader.DrawString(M_GameOver.MS_Position.x, M_GameOver.MS_Position.y, "GameOver", Math::Color{ 1, 1, 1, 1 });
}

// デバッグ表示させたいものはここに書く。
void C_GameOverScene::ImGuiUpdate()
{

}

// 解放処理
void C_GameOverScene::Release()
{

}
