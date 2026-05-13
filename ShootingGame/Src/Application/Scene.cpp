// C_・・・クラス
// M_・・・メンバ
// A_・・・引数
// E_・・・列挙体
// S_・・・構造体
// P_・・・ポインター
// F_・・・フラグ

#include "main.h"
#include "Scene.h"
#include "SceneTranslation/SceneManager&State/SceneManager.h"

// 描画内容はここに
void Scene::Draw2D()
{
	for (int i = 0; i < M_BackTexMAX; i++)
	{
		SHADER.m_spriteShader.SetMatrix(M_BackMat[i]);
		SHADER.m_spriteShader.DrawColorTex(&M_BackTex[i], Math::Rectangle{ 0, 0, 1280, 720 }, Math::Color{ 1, 1, 1, 1 });
	}

	for (int i = 0; i < M_StarNumMAX; i++)
	{
		for (int j = 0; j < M_StarTexMAX; j++)
		{
			SHADER.m_spriteShader.SetMatrix(M_StarMat[i][j]);
			SHADER.m_spriteShader.DrawTex(&M_StarTex[i][j], Math::Rectangle{0, 0, 1280, 720}, 1.0f);
		}
	}


	// それぞれのシーン(ゲーム場面)の描画処理
	C_SceneManager::Instance().Draw();
}

// 更新内容はここに
void Scene::Update()
{
	if (GetAsyncKeyState('U') & 0x8000) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_Title); }
	if (GetAsyncKeyState('I') & 0x8000) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_MainGame); }
	if (GetAsyncKeyState('O') & 0x8000) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_Result); }
	if (GetAsyncKeyState('P') & 0x8000) { C_SceneManager::Instance().SetterNextScene(C_SceneManager::E_SceneType::ME_GameOver); }

	for (int i = 0; i < M_BackTexMAX; i++) { M_BackPos[i].x += -10; }

	if (M_BackPos[0].x < -1280)
	{
		M_BackPos[0].x = M_BackPos[3].x + 1280;
	}
	if (M_BackPos[1].x < -1280)
	{
		M_BackPos[1].x = M_BackPos[0].x + 1280;
	}
	if (M_BackPos[2].x < -1280)
	{
		M_BackPos[2].x = M_BackPos[1].x + 1280;
	}
	if (M_BackPos[3].x < -1280)
	{
		M_BackPos[3].x = M_BackPos[2].x + 1280;
	}

	for (int i = 0; i < M_StarTexMAX; i++) { M_StarPos[0][i].x += -5; }

	if (M_StarPos[0][0].x < -1280)
	{
		M_StarPos[0][0].x = M_StarPos[0][2].x + 1280;
	}
	if (M_StarPos[0][1].x < -1280)
	{
		M_StarPos[0][1].x = M_StarPos[0][0].x + 1280;
	}
	if (M_StarPos[0][2].x < -1280)
	{
		M_StarPos[0][2].x = M_StarPos[0][1].x + 1280;
	}

	for (int i = 0; i < M_StarTexMAX; i++) { M_StarPos[1][i].x += -4; }

	if (M_StarPos[1][0].x < -1280)
	{
		M_StarPos[1][0].x = M_StarPos[1][2].x + 1280;
	}
	if (M_StarPos[1][1].x < -1280)
	{
		M_StarPos[1][1].x = M_StarPos[1][0].x + 1280;
	}
	if (M_StarPos[1][2].x < -1280)
	{
		M_StarPos[1][2].x = M_StarPos[1][1].x + 1280;
	}

	for (int i = 0; i < M_StarTexMAX; i++) { M_StarPos[2][i].x += -3; }

	if (M_StarPos[2][0].x < -1280)
	{
		M_StarPos[2][0].x = M_StarPos[2][2].x + 1280;
	}
	if (M_StarPos[2][1].x < -1280)
	{
		M_StarPos[2][1].x = M_StarPos[2][0].x + 1280;
	}
	if (M_StarPos[2][2].x < -1280)
	{
		M_StarPos[2][2].x = M_StarPos[2][1].x + 1280;
	}

	Math::Matrix Trans[M_BackTexMAX];
	for (int i = 0; i < M_BackTexMAX; i++)
	{
		Trans[i] = Math::Matrix::CreateTranslation(M_BackPos[i].x, M_BackPos[i].y, 0);
		M_BackMat[i] = Trans[i];
	}

	for (int i = 0; i < M_StarNumMAX; i++)
	{
		for (int j = 0; j < M_StarTexMAX; j++)
		{
			M_StarMat[i][j] = Math::Matrix::CreateTranslation(M_StarPos[i][j].x, M_StarPos[i][j].y, 0);
			M_StarMat[i][j] = Math::Matrix::CreateTranslation(M_StarPos[i][j].x, M_StarPos[i][j].y, 0);
			M_StarMat[i][j] = Math::Matrix::CreateTranslation(M_StarPos[i][j].x, M_StarPos[i][j].y, 0);
		}
	}

	// メインの更新前に行う更新処理
	C_SceneManager::Instance().PreUpdate();

	// それぞれのシーン(ゲーム場面)の更新処理
	C_SceneManager::Instance().Update();

	// メインの更新後に行う更新処理
	C_SceneManager::Instance().PostUpdate();

}

// 初期化内容はここに
void Scene::Init()
{
	// 取り出す数値をシャッフルする。
	srand(timeGetTime());

	M_BackTex[0].Load("Texture/背景２.png");
	M_BackTex[1].Load("Texture/背景５.png");
	M_BackTex[2].Load("Texture/背景２.png");
	M_BackTex[3].Load("Texture/背景５.png");

	for (int i = 0; i < M_StarTexMAX; i++) { M_StarTex[0][i].Load("Texture/背景３.png"); }
	
	for (int i = 0; i < M_StarTexMAX; i++) { M_StarTex[1][i].Load("Texture/背景６.png"); }
	
	for (int i = 0; i < M_StarTexMAX; i++) { M_StarTex[2][i].Load("Texture/背景７.png"); }

	M_BackPos[0] = { 0, 0 };
	M_BackPos[1] = { 1280, 0 };
	M_BackPos[2] = { 1280 * 2, 0 };
	M_BackPos[3] = { 1280 * 3, 0 };

	for (int i = 0; i < M_StarNumMAX; i++)
	{
		M_StarPos[i][0] = { 0, 0 };
		M_StarPos[i][1] = { 1280, 0 };
		M_StarPos[i][2] = { 2560, 0 };
	}

	C_SceneManager::Instance().Init();
}

// 最後に解放したいものはここに
void Scene::Release()
{
	for (int i = 0; i < M_BackTexMAX; i++) { M_BackTex[i].Release(); }

	for (int i = 0; i < M_StarNumMAX; i++)
	{
		for (int j = 0; j < M_StarTexMAX; j++)
		{
			M_StarTex[i][j].Release();
			M_StarTex[i][j].Release();
			M_StarTex[i][j].Release();
		}
	}

}

// デバッグ画面に表示するものはここに
void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		C_SceneManager::Instance().ImGuiUpdate();
	}
	ImGui::End();
}

