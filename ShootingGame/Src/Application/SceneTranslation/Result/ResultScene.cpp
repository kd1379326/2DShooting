#include "ResultScene.h"

// シーン遷移を行うクラス
#include "../SceneManager&State/SceneManager.h"

#include "../../Scene.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_ResultScene::C_ResultScene()
{
	M_Black.MS_Texture.Load("Texture/ResultBlack.png");
	M_Back.MS_Texture.Load("Texture/背景２.png");
	M_Logo.MS_Texture.Load("Texture/GameClear.png");
	M_Press.MS_Texture.Load("Texture/ClearReturnTitle.png");
	M_Rank.MS_Texture.Load("Texture/Rank.png");
	M_MainChara.MS_Texture.Load("Texture/MainCharacter/MainCharacter.png");

	for (int i = 0; i < 7; i++) { M_UIMainCharaNotHP[i].MS_Texture.Load("Texture/UIHP2.png"); }

	for (int i = 0; i < M_MainCharaMAXHP; i++)
	{ 
		M_UIMainCharaHP[i].MS_Texture.Load("Texture/UIHP1.png"); 
	}


	M_Black.MS_Position = { 0, -60 };
	M_Back.MS_Position = { 0, 0 };
	M_Logo.MS_Position = { 640 + 407, 250 };
	M_Press.MS_Position = { 640 + 407, -250 };
	M_Rank.MS_Position = { 50, -100 };
	M_MainChara.MS_Position = { -250, -100 };

	M_UIMainCharaNotHP[0].MS_Position = { -150, -100 };
	M_UIMainCharaHP[0].MS_Position = { -150, -100 };
	for (int i = 1; i < 7; i++) { M_UIMainCharaNotHP[i].MS_Position = { M_UIMainCharaNotHP[0].MS_Position.x + (float)(9 * i), -100 }; }
	for (int i = 1; i < M_MainCharaMAXHP; i++) { M_UIMainCharaHP[i].MS_Position = M_UIMainCharaNotHP[i].MS_Position; }

	switch (SCENE.Getter_MainCharaHP())
	{
	case 7:
	{
		M_RankC.MS_Texture.Load("Texture/S.png");
		M_RankC.MS_Position = { 240, -60 };
		break;
	}
	case 6:
	{
		M_RankC.MS_Texture.Load("Texture/A.png");
		M_RankC.MS_Position = { 230, -70 };
		break;
	}
	case 5:
	{
		M_RankC.MS_Texture.Load("Texture/A.png");
		M_RankC.MS_Position = { 230, -70 };
		break;
	}
	case 4:
	{
		M_RankC.MS_Texture.Load("Texture/B.png");
		M_RankC.MS_Position = { 220, -80 };
		break;
	}
	case 3:
	{
		M_RankC.MS_Texture.Load("Texture/B.png");
		M_RankC.MS_Position = { 220, -80 };
		break;
	}
	case 2:
	{
		M_RankC.MS_Texture.Load("Texture/C.png");
		M_RankC.MS_Position = { 210, -90 };
		break;
	}
	case 1:
	{
		M_RankC.MS_Texture.Load("Texture/C.png");
		M_RankC.MS_Position = { 210, -90 };
		break;
	}
	default:
	{
		M_RankC.MS_Texture.Load("Texture/C.png");
		M_RankC.MS_Position = { 210, -90 };
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
	if ((GetAsyncKeyState('Z') & 0x8000) && (!MF_Stop_ContinuitySceneTransition)) { MF_StartFlag = true; M_RankDelta = -0.03f; }
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

	if (M_Logo.MS_Position.x <= 0)
	{
		M_RankAlpha += M_RankDelta;
		if (M_RankAlpha > 1) { M_RankAlpha = 1; }
		if (M_RankAlpha < 0) { M_RankAlpha = 0; }
	}

	M_Press.MS_Position.x -= 20;
	if ((M_Press.MS_Position.x < 0) && !MF_StartFlag) { M_Press.MS_Position.x = 0; }

	//M_Rank.MS_Position.x -= 20;
	//if ((M_Rank.MS_Position.x < 50) && !MF_StartFlag) { M_Rank.MS_Position.x = 50; }

	//M_MainChara.MS_Position.x -= 20;
	//if ((M_MainChara.MS_Position.x < -250) && !MF_StartFlag) { M_MainChara.MS_Position.x = -250; }


	//M_RankC.MS_Position.x -= 20;
	//switch (SCENE.Getter_MainCharaHP())
	//{
	//case 7:
	//{
	//	if ((M_RankC.MS_Position.x < 240) && !MF_StartFlag) { M_RankC.MS_Position.x = 240; }
	//	break;
	//}
	//case 6:
	//{
	//	if ((M_RankC.MS_Position.x < 230) && !MF_StartFlag) { M_RankC.MS_Position.x = 230; }
	//	break;
	//}
	//case 5:
	//{
	//	if ((M_RankC.MS_Position.x < 230) && !MF_StartFlag) { M_RankC.MS_Position.x = 230; }
	//	break;
	//}
	//case 4:
	//{
	//	if ((M_RankC.MS_Position.x < 220) && !MF_StartFlag) { M_RankC.MS_Position.x = 220; }
	//	break;
	//}
	//case 3:
	//{
	//	if ((M_RankC.MS_Position.x < 220) && !MF_StartFlag) { M_RankC.MS_Position.x = 220; }
	//	break;
	//}
	//case 2:
	//{
	//	if ((M_RankC.MS_Position.x < 210) && !MF_StartFlag) { M_RankC.MS_Position.x = 210; }
	//	break;
	//}
	//case 1:
	//{
	//	if ((M_RankC.MS_Position.x < 210) && !MF_StartFlag) { M_RankC.MS_Position.x = 210; }
	//	break;
	//}
	//default:
	//{
	//	if ((M_RankC.MS_Position.x < 210) && !MF_StartFlag) { M_RankC.MS_Position.x = 210; }
	//	break;
	//}
	//}


	M_Black.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Black.MS_Position.x, M_Black.MS_Position.y, 0);
	M_Back.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Back.MS_Position.x, M_Back.MS_Position.y, 0);
	M_Logo.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Logo.MS_Position.x, M_Logo.MS_Position.y, 0);
	M_Press.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Press.MS_Position.x, M_Press.MS_Position.y, 0);
	M_Rank.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Rank.MS_Position.x, M_Rank.MS_Position.y, 0);
	M_RankC.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_RankC.MS_Position.x, M_RankC.MS_Position.y, 0);


	for (int i = 0; i < 7; i++) { M_UIMainCharaNotHP[i].MS_Matrix = Math::Matrix::CreateTranslation(M_UIMainCharaNotHP[i].MS_Position.x, M_UIMainCharaNotHP[i].MS_Position.y, 0); }
	for (int i = 0; i < SCENE.Getter_MainCharaHP(); i++) { M_UIMainCharaHP[i].MS_Matrix = M_UIMainCharaNotHP[i].MS_Matrix; }


	Math::Matrix Rotate = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(-90));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(M_MainChara.MS_Position.x, M_MainChara.MS_Position.y, 0);
	M_MainChara.MS_Matrix = Rotate * Trans;

	M_Black.MS_Matrix = M_Black.MS_TranslationMatrix;
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

	SHADER.m_spriteShader.SetMatrix(M_Black.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Black.MS_Texture, Math::Rectangle{ 0, 0, 844, 250 }, M_RankAlpha);

	SHADER.m_spriteShader.SetMatrix(M_Logo.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Logo.MS_Texture, Math::Rectangle{ 0, 0, 814, 166 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Press.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Press.MS_Texture, Math::Rectangle{ 0, 0, 284, 89 }, M_Alpha);

	SHADER.m_spriteShader.SetMatrix(M_Rank.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_Rank.MS_Texture, Math::Rectangle{ 0, 0, 182, 91 }, M_RankAlpha);

	for (int i = 1; i < 7; i++)
	{
		SHADER.m_spriteShader.SetMatrix(M_UIMainCharaNotHP[i].MS_Matrix);
		SHADER.m_spriteShader.DrawColorTex(&M_UIMainCharaNotHP[i].MS_Texture, Math::Rectangle{ 0, 0, 6, 58 }, Math::Color{ 1, 1, 1, M_RankAlpha });
	}

	for (int i = 0; i < SCENE.Getter_MainCharaHP(); i++)
	{
		SHADER.m_spriteShader.SetMatrix(M_UIMainCharaHP[i].MS_Matrix);
		SHADER.m_spriteShader.DrawColorTex(&M_UIMainCharaHP[i].MS_Texture, Math::Rectangle{ 0, 0, 6, 58 }, Math::Color{ 1, 1, 1, M_RankAlpha });
	}

	SHADER.m_spriteShader.SetMatrix(M_RankC.MS_Matrix);
	switch (SCENE.Getter_MainCharaHP())
	{
	case 7:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 188, 222 }, M_RankAlpha);
		break;
	}
	case 6:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 175, 192 }, M_RankAlpha);
		break;
	}
	case 5:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 175, 192 }, M_RankAlpha);
		break;
	}
	case 4:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 148, 160 }, M_RankAlpha);
		break;
	}
	case 3:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 148, 160 }, M_RankAlpha);
		break;
	}
	case 2:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 112, 130 }, M_RankAlpha);
		break;
	}
	case 1:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 112, 130 }, M_RankAlpha);
		break;
	}
	default:
	{
		SHADER.m_spriteShader.DrawTex(&M_RankC.MS_Texture, Math::Rectangle{ 0, 0, 112, 130 }, M_RankAlpha);
		break;
	}
	}


	// 画像の切り取り範囲
	int Anime[6] = { 0, 52, 104, 156, 104, 52 };
	Math::Rectangle RcMainChara = { Anime[(int)M_Anime], 0, 52, 64 };
	SHADER.m_spriteShader.SetMatrix(M_MainChara.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_MainChara.MS_Texture, RcMainChara, M_RankAlpha);



}

// デバッグ画面に出したい内容はここに
void C_ResultScene::ImGuiUpdate()
{
	ImGui::Text("HP : %d", SCENE.Getter_MainCharaHP());
	ImGui::SliderFloat(u8"太陽の数", &M_UIMainCharaHP[0].MS_Position.x, -640, 640);
}

// 解放処理
void C_ResultScene::Release()
{
	M_Black.MS_Texture.Release();
	M_Back.MS_Texture.Release();
	M_Logo.MS_Texture.Release();
	M_Press.MS_Texture.Release();
	M_Rank.MS_Texture.Release();
	M_MainChara.MS_Texture.Release();
	M_RankC.MS_Texture.Release();
	for (int i = 1; i < 7; i++) { M_UIMainCharaNotHP[i].MS_Texture.Release(); }
	for (int i = 0; i < M_MainCharaMAXHP; i++) { M_UIMainCharaHP[i].MS_Texture.Release(); }
}