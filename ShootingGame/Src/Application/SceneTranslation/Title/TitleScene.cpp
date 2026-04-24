#include "TitleScene.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_TitleScene::C_TitleScene()
{
	M_Title.MS_Pos = { 0, 0 };
	
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_TitleScene::~C_TitleScene()
{

}

// 初期化内容はここに
void C_TitleScene::Init()
{

}

// 更新内容はここに
void C_TitleScene::Update()
{

}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_TitleScene::Draw()
{
	SHADER.m_spriteShader.DrawString(M_Title.MS_Pos.x, M_Title.MS_Pos.y, "Title", { 1.0f, 1.0f, 1.0f, 1.0f });
}

// デバッグ画面に出したい内容はここに
void C_TitleScene::ImGuiUpdate()
{

}