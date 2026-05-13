#include "TitleScene.h"

// シーン遷移を行うクラス
#include "../SceneManager&State/SceneManager.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_TitleScene::C_TitleScene()
{
	M_Title.MS_Texture.Load("Texture/背景１.png");
	M_Logo.MS_Texture.Load("Texture/TitleLogo.png");
	M_Press.MS_Texture.Load("Texture/TitleStart.png");
	M_MainChara.MS_Texture.Load("Texture/MainCharacter/MainCharacter.png");
	M_Title.MS_Position = { 0, 0 };
	M_Logo.MS_Position = { 640 + 385, 125 };
	M_Press.MS_Position = { 640 + 385, -200 };
	M_MainChara.MS_Position = { -640 + -32, 0 };
	// シーン遷移させないようフラグを立てる。
	MF_Stop_ContinuitySceneTransition = true;
	MF_StartFlag = false;
	
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
	if (!(GetAsyncKeyState('Z') & 0x8000)) { MF_Stop_ContinuitySceneTransition = false; }
	// 条件１：ENTERキーが押された
	// 条件２：シーン遷移のストッパーが外れている
	if ((GetAsyncKeyState('Z') & 0x8000) && (!MF_Stop_ContinuitySceneTransition)) { MF_StartFlag = true; }
	if (M_MainChara.MS_Position.x == -500) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_MainGame); }

	M_Logo.MS_Position.x -= 20;
	if ((M_Logo.MS_Position.x < 0) && !MF_StartFlag) { M_Logo.MS_Position.x = 0; }

	if (M_Logo.MS_Position.x == 0 && !MF_StartFlag)
	{
		if (M_Alpha <= 0.3f) { M_Delta = 0.02f; }
		if (M_Alpha >= 1) { M_Delta = -0.02f; }
		M_Alpha += M_Delta;
	}

	M_Anime += 0.5f;
	if (M_Anime >= 6)
	{
		M_Anime = 0;
	}

	M_Press.MS_Position.x -= 20;
	if ((M_Press.MS_Position.x < 0) && !MF_StartFlag) { M_Press.MS_Position.x = 0; }

	if (M_Logo.MS_Position.x < -640 + -385){ M_MainChara.MS_Position.x += 5; }
	if (M_MainChara.MS_Position.x > -500) { M_MainChara.MS_Position.x = -500; }

	M_Title.MS_Matrix = Math::Matrix::CreateTranslation(0, 0, 0);
	M_Logo.MS_Matrix = Math::Matrix::CreateTranslation(M_Logo.MS_Position.x, M_Logo.MS_Position.y, 0);
	M_Press.MS_Matrix = Math::Matrix::CreateTranslation(M_Press.MS_Position.x, M_Press.MS_Position.y, 0);

	Math::Matrix Rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(-90));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(M_MainChara.MS_Position.x, M_MainChara.MS_Position.y, 0);
	M_MainChara.MS_Matrix = Rotate * Trans;

}

// 更新後に行いたい更新処理はここに書く。
void C_TitleScene::PostUpdate()
{

}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_TitleScene::DrawSprite()
{
	//SHADER.m_spriteShader.DrawString(M_Title.MS_Position.x, M_Title.MS_Position.y, "Title", { 1.0f, 1.0f, 1.0f, 1.0f });
	//SHADER.m_spriteShader.SetMatrix(M_Title.MS_Matrix);
	//SHADER.m_spriteShader.DrawColorTex(&M_Title.MS_Texture, Math::Rectangle{ 0, 0, 1280, 720 }, Math::Color {1, 1, 1, 1 });
	SHADER.m_spriteShader.SetMatrix(M_Logo.MS_Matrix);
	SHADER.m_spriteShader.DrawColorTex(&M_Logo.MS_Texture, Math::Rectangle{ 0, 0, 770, 178 }, Math::Color {1, 1, 1, 1 });
	SHADER.m_spriteShader.SetMatrix(M_Press.MS_Matrix);
	SHADER.m_spriteShader.DrawColorTex(&M_Press.MS_Texture, Math::Rectangle{ 0, 0, 398, 80 }, Math::Color {1, 1, 1, M_Alpha });

	int Anime[6] = { 0, 52, 104, 156, 104, 52 };
	Math::Rectangle RcMainChara = { Anime[(int)M_Anime], 0, 52, 64 };
	SHADER.m_spriteShader.SetMatrix(M_MainChara.MS_Matrix);
	SHADER.m_spriteShader.DrawColorTex(&M_MainChara.MS_Texture, RcMainChara, Math::Color {1, 1, 1, 1 });
}

// デバッグ画面に出したい内容はここに
void C_TitleScene::ImGuiUpdate()
{

}

// 解放処理
void C_TitleScene::Release()
{
	M_Title.MS_Texture.Release();
	M_Logo.MS_Texture.Release();
	M_Press.MS_Texture.Release();
	M_MainChara.MS_Texture.Release();
}