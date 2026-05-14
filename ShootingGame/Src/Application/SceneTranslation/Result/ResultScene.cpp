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
	M_Rank.MS_Texture.Load("Texture/Rank.png");
	M_MainChara.MS_Texture.Load("Texture/MainCharacter/MainCharacter.png");




	M_Back.MS_Position = { 0, 0 };
	M_Logo.MS_Position = { 640 + 407, 250 };
	M_Press.MS_Position = { 640 + 407, -250 };
	M_Rank.MS_Position = { 640 + 407 + 100, -100 };
	M_MainChara.MS_Position = { -300, -100 };

	switch (SCENE.Getter_MainCharaHP())
	{
	case 7:
	{
		M_RankC.MS_Texture.Load("Texture/S.png");
		M_RankC.MS_Position = { 640 + 407 + 290, -60 };
		break;
	}
	case 6:
	{
		M_RankC.MS_Texture.Load("Texture/A.png");
		M_RankC.MS_Position = { 640 + 407 + 280, -70 };
		break;
	}
	case 5:
	{
		M_RankC.MS_Texture.Load("Texture/A.png");
		M_RankC.MS_Position = { 640 + 407 + 280, -70 };
		break;
	}
	case 4:
	{
		M_RankC.MS_Texture.Load("Texture/B.png");
		M_RankC.MS_Position = { 640 + 407 + 270, -80 };
		break;
	}
	case 3:
	{
		M_RankC.MS_Texture.Load("Texture/B.png");
		M_RankC.MS_Position = { 640 + 407 + 270, -80 };
		break;
	}
	case 2:
	{
		M_RankC.MS_Texture.Load("Texture/C.png");
		M_RankC.MS_Position = { 640 + 407 + 260, -90 };
		break;
	}
	case 1:
	{
		M_RankC.MS_Texture.Load("Texture/C.png");
		M_RankC.MS_Position = { 640 + 407 + 260, -90 };
		break;
	}
	default:
	{
		M_RankC.MS_Texture.Load("Texture/C.png");
		M_RankC.MS_Position = { 640 + 407 + 260, -90 };
		break;
	}
	}




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

	M_Anime += 0.5f;
	if (M_Anime >= 6)
	{
		M_Anime = 0;
	}

	M_Press.MS_Position.x -= 20;
	if ((M_Press.MS_Position.x < 0) && !MF_StartFlag) { M_Press.MS_Position.x = 0; }

	M_Rank.MS_Position.x -= 20;
	if ((M_Rank.MS_Position.x < 100) && !MF_StartFlag) { M_Rank.MS_Position.x = 100; }

	M_MainChara.MS_Position.x -= 20;
	if ((M_MainChara.MS_Position.x < -300) && !MF_StartFlag) { M_MainChara.MS_Position.x = -300; }

	M_RankC.MS_Position.x -= 20;


	switch (SCENE.Getter_MainCharaHP())
	{
	case 7:
	{
		if ((M_RankC.MS_Position.x < 290) && !MF_StartFlag) { M_RankC.MS_Position.x = 290; }
		break;
	}
	case 6:
	{
		if ((M_RankC.MS_Position.x < 280) && !MF_StartFlag) { M_RankC.MS_Position.x = 280; }
		break;
	}
	case 5:
	{
		if ((M_RankC.MS_Position.x < 280) && !MF_StartFlag) { M_RankC.MS_Position.x = 280; }
		break;
	}
	case 4:
	{
		if ((M_RankC.MS_Position.x < 270) && !MF_StartFlag) { M_RankC.MS_Position.x = 270; }
		break;
	}
	case 3:
	{
		if ((M_RankC.MS_Position.x < 270) && !MF_StartFlag) { M_RankC.MS_Position.x = 270; }
		break;
	}
	case 2:
	{
		if ((M_RankC.MS_Position.x < 260) && !MF_StartFlag) { M_RankC.MS_Position.x = 260; }
		break;
	}
	case 1:
	{
		if ((M_RankC.MS_Position.x < 260) && !MF_StartFlag) { M_RankC.MS_Position.x = 260; }
		break;
	}
	default:
	{
		if ((M_RankC.MS_Position.x < 260) && !MF_StartFlag) { M_RankC.MS_Position.x = 260; }
		break;
	}
	}


	M_Back.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Back.MS_Position.x, M_Back.MS_Position.y, 0);
	M_Logo.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Logo.MS_Position.x, M_Logo.MS_Position.y, 0);
	M_Press.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Press.MS_Position.x, M_Press.MS_Position.y, 0);
	M_Rank.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Rank.MS_Position.x, M_Rank.MS_Position.y, 0);
	M_RankC.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_RankC.MS_Position.x, M_RankC.MS_Position.y, 0);

	Math::Matrix Rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(-90));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(M_MainChara.MS_Position.x, M_MainChara.MS_Position.y, 0);
	M_MainChara.MS_Matrix = Rotate * Trans;

	M_Back.MS_Matrix = M_Back.MS_TranslationMatrix;
	M_Logo.MS_Matrix = M_Logo.MS_TranslationMatrix;
	M_Press.MS_Matrix = M_Press.MS_TranslationMatrix;
	M_Rank.MS_Matrix = M_Rank.MS_TranslationMatrix;
	M_RankC.MS_Matrix = M_RankC.MS_TranslationMatrix;


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

	SHADER.m_spriteShader.SetMatrix(M_Rank.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Rank.MS_Texture, Math::Rectangle{ 0, 0, 182, 91 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_RankC.MS_Matrix);
	switch (SCENE.Getter_MainCharaHP())
	{
	case 7:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 188, 222 }, 1.0f);
		break;
	}
	case 6:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 175, 192 }, 1.0f);
		break;
	}
	case 5:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 175, 192 }, 1.0f);
		break;
	}
	case 4:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 148, 160 }, 1.0f);
		break;
	}
	case 3:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 148, 160 }, 1.0f);
		break;
	}
	case 2:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 112, 130 }, 1.0f);
		break;
	}
	case 1:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 112, 130 }, 1.0f);
		break;
	}
	default:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 112, 130 }, 1.0f);
		break;
	}
	}


	// 画像の切り取り範囲
	int Anime[6] = { 0, 52, 104, 156, 104, 52 };
	Math::Rectangle RcMainChara = { Anime[(int)M_Anime], 0, 52, 64 };
	SHADER.m_spriteShader.SetMatrix(M_MainChara.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_MainChara.MS_Texture, RcMainChara, 1.0f);


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
	M_Rank.MS_Texture.Release();
	M_MainChara.MS_Texture.Release();
	M_RankC.MS_Texture.Release();
}