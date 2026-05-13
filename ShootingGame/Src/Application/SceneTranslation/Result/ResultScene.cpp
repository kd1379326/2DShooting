#include "ResultScene.h"

// シーン遷移を行うクラス
#include "../SceneManager&State/SceneManager.h"

#include "../../Scene.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_ResultScene::C_ResultScene()
{
	M_Back.MS_Texture.Load("Texture/背景２.png");
	M_Logo.MS_Texture.Load("Texture/GameClear.png");
	M_Press.MS_Texture.Load("Texture/ClearReturnTitle.png");
	M_Back.MS_Position = { 0, 0 };
	M_Logo.MS_Position = { 640 + 407, 150 };
	M_Press.MS_Position = { 640 + 407, -200 };
	// シーン遷移させないようフラグを立てる。
	MF_Stop_ContinuitySceneTransition = true;
	MF_StartFlag = false;

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
	if (!(GetAsyncKeyState('Z') & 0x8000)) { MF_Stop_ContinuitySceneTransition = false; }
	// 条件１：ENTERキーが押された
	// 条件２：シーン遷移のストッパーが外れている
	if ((GetAsyncKeyState('Z') & 0x8000) && (!MF_Stop_ContinuitySceneTransition)) { MF_StartFlag = true; }
	if (M_Logo.MS_Position.x < (-640 + -407)) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_Title); }

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
void C_ResultScene::PostUpdate()
{

}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_ResultScene::DrawSprite()
{
	//SHADER.m_spriteShader.DrawString(M_Result.MS_Position.x, M_Result.MS_Position.y, "Result", { 1.0f, 1.0f, 1.0f, 1.0f });

	//SHADER.m_spriteShader.SetMatrix(M_Back.MS_Matrix);
	//SHADER.m_spriteShader.DrawTex(&M_Back.MS_Texture, Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Logo.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Logo.MS_Texture, Math::Rectangle{ 0, 0, 814, 166 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Press.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Press.MS_Texture, Math::Rectangle{ 0, 0, 284, 89 }, M_Alpha);


}

// デバッグ画面に出したい内容はここに
void C_ResultScene::ImGuiUpdate()
{
	ImGui::Text("HP : %d", SCENE.Getter_MainCharaHP());
}

// 解放処理
void C_ResultScene::Release()
{
	M_Back.MS_Texture.Release();
	M_Logo.MS_Texture.Release();
	M_Press.MS_Texture.Release();
}