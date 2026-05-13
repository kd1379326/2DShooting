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
	SHADER.m_spriteShader.SetMatrix(M_BackMat[0]);
	SHADER.m_spriteShader.DrawColorTex(&M_BackTex[0], Math::Rectangle{ 0, 0, 1280, 720 }, Math::Color { 1, 1, 1, 1});

	SHADER.m_spriteShader.SetMatrix(M_BackMat[1]);
	SHADER.m_spriteShader.DrawColorTex(&M_BackTex[1], Math::Rectangle{ 0, 0, 1280, 720 }, Math::Color{ 1, 1, 1, 1 });

	SHADER.m_spriteShader.SetMatrix(M_BackMat[2]);
	SHADER.m_spriteShader.DrawColorTex(&M_BackTex[2], Math::Rectangle{ 0, 0, 1280, 720 }, Math::Color{ 1, 1, 1, 1 });

	SHADER.m_spriteShader.SetMatrix(M_BackMat[3]);
	SHADER.m_spriteShader.DrawColorTex(&M_BackTex[3], Math::Rectangle{ 0, 0, 1280, 720 }, Math::Color{ 1, 1, 1, 1 });

	SHADER.m_spriteShader.SetMatrix(M_Star1Mat[0]);
	SHADER.m_spriteShader.DrawTex(&M_Star1Tex[0], Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Star1Mat[1]);
	SHADER.m_spriteShader.DrawTex(&M_Star1Tex[1], Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Star1Mat[2]);
	SHADER.m_spriteShader.DrawTex(&M_Star1Tex[2], Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);


	SHADER.m_spriteShader.SetMatrix(M_Star2Mat[0]);
	SHADER.m_spriteShader.DrawTex(&M_Star2Tex[0], Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Star2Mat[1]);
	SHADER.m_spriteShader.DrawTex(&M_Star2Tex[1], Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Star2Mat[2]);
	SHADER.m_spriteShader.DrawTex(&M_Star2Tex[2], Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);


	SHADER.m_spriteShader.SetMatrix(M_Star3Mat[0]);
	SHADER.m_spriteShader.DrawTex(&M_Star3Tex[0], Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Star3Mat[1]);
	SHADER.m_spriteShader.DrawTex(&M_Star3Tex[1], Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	SHADER.m_spriteShader.SetMatrix(M_Star3Mat[2]);
	SHADER.m_spriteShader.DrawTex(&M_Star3Tex[2], Math::Rectangle{ 0, 0, 1280, 720 }, 1.0f);

	// それぞれのシーン(ゲーム場面)の描画処理
	C_SceneManager::Instance().Draw();
}

// 更新内容はここに
void Scene::Update()
{
	M_BackPos[0].x += -10;
	M_BackPos[1].x += -10;
	M_BackPos[2].x += -10;
	M_BackPos[3].x += -10;
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




	M_Star1Pos[0].x += -5;
	M_Star1Pos[1].x += -5;
	M_Star1Pos[2].x += -5;

	if (M_Star1Pos[0].x < -1280)
	{
		M_Star1Pos[0].x = M_Star1Pos[2].x + 1280;
	}
	if (M_Star1Pos[1].x < -1280)
	{
		M_Star1Pos[1].x = M_Star1Pos[0].x + 1280;
	}
	if (M_Star1Pos[2].x < -1280)
	{
		M_Star1Pos[2].x = M_Star1Pos[1].x + 1280;
	}

	M_Star2Pos[0].x += -4;
	M_Star2Pos[1].x += -4;
	M_Star2Pos[2].x += -4;

	if (M_Star2Pos[0].x < -1280)
	{
		M_Star2Pos[0].x = M_Star2Pos[2].x + 1280;
	}
	if (M_Star2Pos[1].x < -1280)
	{
		M_Star2Pos[1].x = M_Star2Pos[0].x + 1280;
	}
	if (M_Star2Pos[2].x < -1280)
	{
		M_Star2Pos[2].x = M_Star2Pos[1].x + 1280;
	}


	M_Star3Pos[0].x += -3;
	M_Star3Pos[1].x += -3;
	M_Star3Pos[2].x += -3;

	if (M_Star3Pos[0].x < -1280)
	{
		M_Star3Pos[0].x = M_Star3Pos[2].x + 1280;
	}
	if (M_Star3Pos[1].x < -1280)
	{
		M_Star3Pos[1].x = M_Star3Pos[0].x + 1280;
	}
	if (M_Star3Pos[2].x < -1280)
	{
		M_Star3Pos[2].x = M_Star3Pos[1].x + 1280;
	}



	Math::Matrix Trans0 = Math::Matrix::CreateTranslation(M_BackPos[0].x, M_BackPos[0].y, 0);
	Math::Matrix Trans1 = Math::Matrix::CreateTranslation(M_BackPos[1].x, M_BackPos[1].y, 0);
	Math::Matrix Trans2 = Math::Matrix::CreateTranslation(M_BackPos[2].x, M_BackPos[2].y, 0);
	Math::Matrix Trans3 = Math::Matrix::CreateTranslation(M_BackPos[3].x, M_BackPos[3].y, 0);

	M_BackMat[0] = Trans0;
	M_BackMat[1] = Trans1;
	M_BackMat[2] = Trans2;
	M_BackMat[3] = Trans3;


	M_Star1Mat[0] = Math::Matrix::CreateTranslation(M_Star1Pos[0].x, M_Star1Pos[0].y, 0);
	M_Star1Mat[1] = Math::Matrix::CreateTranslation(M_Star1Pos[1].x, M_Star1Pos[1].y, 0);
	M_Star1Mat[2] = Math::Matrix::CreateTranslation(M_Star1Pos[2].x, M_Star1Pos[2].y, 0);

	M_Star2Mat[0] = Math::Matrix::CreateTranslation(M_Star2Pos[0].x, M_Star2Pos[0].y, 0);
	M_Star2Mat[1] = Math::Matrix::CreateTranslation(M_Star2Pos[1].x, M_Star2Pos[1].y, 0);
	M_Star2Mat[2] = Math::Matrix::CreateTranslation(M_Star2Pos[2].x, M_Star2Pos[2].y, 0);

	M_Star3Mat[0] = Math::Matrix::CreateTranslation(M_Star3Pos[0].x, M_Star3Pos[0].y, 0);
	M_Star3Mat[1] = Math::Matrix::CreateTranslation(M_Star3Pos[1].x, M_Star3Pos[1].y, 0);
	M_Star3Mat[2] = Math::Matrix::CreateTranslation(M_Star3Pos[2].x, M_Star3Pos[2].y, 0);

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

	M_Star1Tex[0].Load("Texture/背景３.png");
	M_Star1Tex[1].Load("Texture/背景３.png");
	M_Star1Tex[2].Load("Texture/背景３.png");

	M_Star2Tex[0].Load("Texture/背景６.png");
	M_Star2Tex[1].Load("Texture/背景６.png");
	M_Star2Tex[2].Load("Texture/背景６.png");

	M_Star3Tex[0].Load("Texture/背景７.png");
	M_Star3Tex[1].Load("Texture/背景７.png");
	M_Star3Tex[2].Load("Texture/背景７.png");

	M_BackPos[0] = { 0, 0 };
	M_BackPos[1] = { 1280, 0 };
	M_BackPos[2] = { 1280 * 2, 0 };
	M_BackPos[3] = { 1280 * 3, 0 };

	M_Star1Pos[0] = { 0, 0 };
	M_Star1Pos[1] = { 1280, 0 };
	M_Star1Pos[2] = { 2560, 0 };

	M_Star2Pos[0] = { 0, 0 };
	M_Star2Pos[1] = { 1280, 0 };
	M_Star2Pos[2] = { 2560, 0 };

	M_Star3Pos[0] = { 0, 0 };
	M_Star3Pos[1] = { 1280, 0 };
	M_Star3Pos[2] = { 2560, 0 };

	C_SceneManager::Instance().Init();
}

// 最後に解放したいものはここに
void Scene::Release()
{
	M_BackTex[0].Release();
	M_BackTex[1].Release();
	M_BackTex[2].Release();
	M_BackTex[3].Release();

	M_Star1Tex[0].Release();
	M_Star1Tex[1].Release();
	M_Star1Tex[2].Release();

	M_Star2Tex[0].Release();
	M_Star2Tex[1].Release();
	M_Star2Tex[2].Release();

	M_Star3Tex[0].Release();
	M_Star3Tex[1].Release();
	M_Star3Tex[2].Release();
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

