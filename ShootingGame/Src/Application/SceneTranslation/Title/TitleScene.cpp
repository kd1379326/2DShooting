#include "TitleScene.h"

// シーン遷移を行うクラス
#include "../SceneManager&State/SceneManager.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_TitleScene::C_TitleScene()
{
	M_Title.MS_Texture.Load("Texture/背景１.png");
	M_Logo.MS_Texture.Load("Texture/TitleLogo.png");
	M_Press.MS_Texture.Load("Texture/TitleStart.png");
	M_Title.MS_Position = { 0, 0 };
	M_Logo.MS_Position = { 0, 250 };
	M_Press.MS_Position = { 0, -200 };
	// シーン遷移させないようフラグを立てる。
	MF_Stop_ContinuitySceneTransition = true;
	
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
	// 遷移後、ENTER押し続けた判定でこのシーンを飛ばされないようにキーを離すまでシーン遷移許可を出さない。
	if (!(GetAsyncKeyState(VK_RETURN) & 0x8000)) { MF_Stop_ContinuitySceneTransition = false; }
	// 条件１：ENTERキーが押された
	// 条件２：シーン遷移のストッパーが外れている
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && (!MF_Stop_ContinuitySceneTransition)) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_MainGame); }

	if (a <= 0.3f) { d = 0.02f; }
	if (a >= 1) { d = -0.02f; }
	a += d;

	M_Title.MS_Matrix = Math::Matrix::CreateTranslation(0, 0, 0);
	M_Logo.MS_Matrix = Math::Matrix::CreateTranslation(M_Logo.MS_Position.x, M_Logo.MS_Position.y, 0);
	M_Press.MS_Matrix = Math::Matrix::CreateTranslation(M_Press.MS_Position.x, M_Press.MS_Position.y, 0);
}

// 更新後に行いたい更新処理はここに書く。
void C_TitleScene::PostUpdate()
{
}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_TitleScene::DrawSprite()
{
	//SHADER.m_spriteShader.DrawString(M_Title.MS_Position.x, M_Title.MS_Position.y, "Title", { 1.0f, 1.0f, 1.0f, 1.0f });
	SHADER.m_spriteShader.SetMatrix(M_Title.MS_Matrix);
	SHADER.m_spriteShader.DrawColorTex(&M_Title.MS_Texture, Math::Rectangle{ 0, 0, 1280, 720 }, Math::Color {1, 1, 1, 1 });
	SHADER.m_spriteShader.SetMatrix(M_Logo.MS_Matrix);
	SHADER.m_spriteShader.DrawColorTex(&M_Logo.MS_Texture, Math::Rectangle{ 0, 0, 472, 119 }, Math::Color {1, 1, 1, 1 });
	SHADER.m_spriteShader.SetMatrix(M_Press.MS_Matrix);
	SHADER.m_spriteShader.DrawColorTex(&M_Press.MS_Texture, Math::Rectangle{ 0, 0, 845, 101 }, Math::Color {1, 1, 1, a });
}

// デバッグ画面に出したい内容はここに
void C_TitleScene::ImGuiUpdate()
{

}

// 解放処理
void C_TitleScene::Release()
{
	M_Title.MS_Texture.Release();
}