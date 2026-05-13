#include "GameOverScene.h"

#include "../../Scene.h"

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
	M_Back.MS_Texture.Load("Texture/背景２.png");
	M_Logo.MS_Texture.Load("Texture/GameOverLogo.png");
	M_Press.MS_Texture.Load("Texture/GameOverReturnTitle.png");

	M_Back.MS_Position = { 0, 0 };
	M_Logo.MS_Position = { 640 + 350, 100 };
	M_Press.MS_Position = { 640 + 350, -200 };

	MF_StartFlag = false;
}

// 更新前に行いたい更新処理はここに書く。
void C_GameOverScene::PreUpdate()
{
}

// 更新処理はここに書く。
void C_GameOverScene::Update()
{
	// 遷移後、ENTER押し続けた判定でこのシーンを飛ばされないようにキーを離すまでシーン遷移許可を出さない。
	if (!(GetAsyncKeyState('Z') & 0x8000)) { MF_Stop_ContinuitySceneTransition = false; }
	// 条件１：ENTERキーが押された
	// 条件２：シーン遷移のストッパーが外れている
	if ((GetAsyncKeyState('Z') & 0x8000) && (!MF_Stop_ContinuitySceneTransition)) { MF_StartFlag = true; }
	if (M_Logo.MS_Position.x < (-640 + -350)) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_Title); }

	M_Logo.MS_Position.x -= 20;
	if ((M_Logo.MS_Position.x < 0) && !MF_StartFlag) { M_Logo.MS_Position.x = 0; }

	if (M_Logo.MS_Position.x == 0)
	{
		if (M_Alpha <= 0.3f) { M_Delta = 0.02f; }
		if (M_Alpha >= 1) { M_Delta = -0.02f; }
		M_Alpha += M_Delta;
	}

	M_Press.MS_Position.x -= 20;
	if ((M_Press.MS_Position.x < 0) && !MF_StartFlag) { M_Press.MS_Position.x = 0; }

	M_Back.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Back.MS_Position.x, M_Back.MS_Position.y, 0);
	M_Logo.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Logo.MS_Position.x, M_Logo.MS_Position.y, 0);
	M_Press.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Press.MS_Position.x, M_Press.MS_Position.y, 0);

	M_Back.MS_Matrix = M_Back.MS_TranslationMatrix;
	M_Logo.MS_Matrix = M_Logo.MS_TranslationMatrix;
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

	//SHADER.m_spriteShader.SetMatrix(M_Back.MS_Matrix);
	//SHADER.m_spriteShader.DrawTex(&M_Back.MS_Texture, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Logo.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Logo.MS_Texture, Math::Rectangle{ 0, 0, 700, 179 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Press.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Press.MS_Texture, Math::Rectangle{ 0, 0, 297, 102 }, M_Alpha);


	

}

// デバッグ表示させたいものはここに書く。
void C_GameOverScene::ImGuiUpdate()
{
	ImGui::Text("Enemy : %d", SCENE.Getter_EnemyAliveNum());
}

// 解放処理
void C_GameOverScene::Release()
{
	M_Back.MS_Texture.Release();
	M_Logo.MS_Texture.Release();
	M_Press.MS_Texture.Release();
}
