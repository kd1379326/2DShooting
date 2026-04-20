#include "MainGameScene.h"

// このクラスが生成された時に処理したい内容はここに
C_MainGameScene::C_MainGameScene()
{
	M_Game.MS_Pos = { 0,0 };
}

// このクラスが削除された時に処理したい内容はここに
C_MainGameScene::~C_MainGameScene()
{

}

// 初期化したい内容はここに
void C_MainGameScene::Init()
{
	CM_MainCharacter.Init();
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_MainGameScene::Update()
{
	CM_MainCharacter.Update();
}

// 描画処理はここに
void C_MainGameScene::Draw()
{
	CM_MainCharacter.Draw();
	//SHADER.m_spriteShader.DrawString(M_Game.MS_Pos.x, M_Game.MS_Pos.y, "Game", { 1.0f, 1.0f, 1.0f, 1.0f });
}

// デバッグ画面に表示させたいものはここに
void C_MainGameScene::ImGuiUpdate()
{

}