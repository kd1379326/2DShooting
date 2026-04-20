#include "MainCharacter.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_MainCharacter::C_MainCharacter()
{
	
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_MainCharacter::~C_MainCharacter()
{
	M_MainCharacter.MS_Texture.Release();
}

// 初期化内容はここに
void C_MainCharacter::Init()
{
	M_MainCharacter.MS_Texture.Load("player.png");
	// 座標
		M_MainCharacter.MS_Pos = { 0, 0 };
	// 画像の切り取り範囲
		M_MainCharacter.MS_Rectangle = { 0, 0, 64, 64 };

	
}

// 更新内容はここに
void C_MainCharacter::Update()
{
	// 表示したい座標を設定する
	M_MainCharacter.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_MainCharacter.MS_Pos.x, M_MainCharacter.MS_Pos.y, 0);

	// 描画の詳細をまとめる
	//M_MainCharacter.MS_Matrix = M_MainCharacter.MS_TranslationMatrix;
	M_MainCharacter.MS_Matrix = Math::Matrix::CreateTranslation(M_MainCharacter.MS_Pos.x, M_MainCharacter.MS_Pos.y, 0);
}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_MainCharacter::Draw()
{
	SHADER.m_spriteShader.SetMatrix(M_MainCharacter.MS_Matrix);
	SHADER.m_spriteShader.DrawTex(&M_MainCharacter.MS_Texture, M_MainCharacter.MS_Rectangle, 1);
	//SHADER.m_spriteShader.DrawString(0, 0, "プレイヤー", Math::Color{ 1,1,1,1 });
}

// デバッグ画面に出したい内容はここに
void C_MainCharacter::ImGuiUpdate()
{

}

// Updateに導入する関数
// 操作処理
void C_MainCharacter::MoveControl()
{

}