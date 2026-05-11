#include "GameOverScene.h"

// シーン遷移を行うクラス
#include "../SceneManager&State/SceneManager.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_GameOverScene::C_GameOverScene()
{
	// シーン遷移させないようフラグを立てる。
	MF_Stop_ContinuitySceneTransition = true;
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
	M_Back.MS_Texture.Load("Texture/背景１.png");
	M_Over.MS_Texture.Load("Texture/GameOverLogo.png");
	M_Press.MS_Texture.Load("Texture/GameOverReturnTitle.png");

	M_Back.MS_Position = { 0, 0 };
	M_Over.MS_Position = { 0, 250 };
	M_Press.MS_Position = { 0, -200 };
}

// 更新前に行いたい更新処理はここに書く。
void C_GameOverScene::PreUpdate()
{
}

// 更新処理はここに書く。
void C_GameOverScene::Update()
{
	// 遷移後、ENTER押し続けた判定でこのシーンを飛ばされないようにキーを離すまでシーン遷移許可を出さない。
	if (!(GetAsyncKeyState(VK_RETURN) & 0x8000)) { MF_Stop_ContinuitySceneTransition = false; }
	// 条件１：ENTERキーが押された
	// 条件２：シーン遷移のストッパーが外れている
	if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && (!MF_Stop_ContinuitySceneTransition)) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_Title); }

	if (a <= 0.3f) { d = 0.02f; }
	if (a >= 1) { d = -0.02f; }
	a += d;

	M_Back.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Back.MS_Position.x, M_Back.MS_Position.y, 0);
	M_Over.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Over.MS_Position.x, M_Over.MS_Position.y, 0);
	M_Press.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Press.MS_Position.x, M_Press.MS_Position.y, 0);

	M_Back.MS_Matrix = M_Back.MS_TranslationMatrix;
	M_Over.MS_Matrix = M_Over.MS_TranslationMatrix;
	M_Press.MS_Matrix = M_Press.MS_TranslationMatrix;
}

// 更新後に行いたい更新処理はここに書く。
void C_GameOverScene::PostUpdate()
{
}

// 描画処理はここに書く。
void C_GameOverScene::DrawSprite()
{
	//KdShaderManager::GetInstance().m_spriteShader.DrawString(M_GameOver.MS_Position.x, M_GameOver.MS_Position.y, "GameOver", Math::Color{ 1, 1, 1, 1 });

	SHADER.m_spriteShader.SetMatrix(M_Back.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Back.MS_Texture, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Over.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Over.MS_Texture, Math::Rectangle{ 0, 0, 447, 111 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Press.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Press.MS_Texture, Math::Rectangle{ 0, 0, 1004, 111 }, a);


	

}

// デバッグ表示させたいものはここに書く。
void C_GameOverScene::ImGuiUpdate()
{

}

// 解放処理
void C_GameOverScene::Release()
{
	M_Back.MS_Texture.Release();
	M_Over.MS_Texture.Release();
	M_Press.MS_Texture.Release();
}
