#include "ResultScene.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_ResultScene::C_ResultScene()
{
	M_Result.MS_Pos = { 0, 0 };

}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_ResultScene::~C_ResultScene()
{

}

// 初期化内容はここに
void C_ResultScene::Init()
{

}

// 更新内容はここに
void C_ResultScene::Update()
{

}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_ResultScene::Draw()
{
	SHADER.m_spriteShader.DrawString(M_Result.MS_Pos.x, M_Result.MS_Pos.y, "Result", { 1.0f, 1.0f, 1.0f, 1.0f });
}

// デバッグ画面に出したい内容はここに
void C_ResultScene::ImGuiUpdate()
{

}