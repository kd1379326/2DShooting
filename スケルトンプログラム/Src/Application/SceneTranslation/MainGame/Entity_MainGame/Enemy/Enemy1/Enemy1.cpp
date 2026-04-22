#include "Enemy1.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_Enemy1_MainGame::C_Enemy1_MainGame()
{
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_Enemy1_MainGame::~C_Enemy1_MainGame()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化内容はここに
void C_Enemy1_MainGame::Init()
{
	// 画像のパス(在処)を伝える
		M_Enemy.MS_Texture.Load("Texture/Star/StarShadow.png");

	// 座標(初期位置)
		M_Enemy.MS_Position = { 0, 0 };
	// 移動量
		M_Enemy.MS_Move = { 0, 0 };
	// 画像の切り取り範囲
		M_Enemy.MS_Rectangle = { 0, 0, 64, 64 };
	// 画像の通常時の色(設定なし)
		M_Enemy.MS_Color_Normal = { 1, 1, 1, 1 };
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_Enemy1_MainGame::Update()
{
	// どこに描画するか座標情報を設定する。
	M_Enemy.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Enemy.MS_Position.x, M_Enemy.MS_Position.y, 0);

	// それぞれの描画情報を行列にまとめる
	M_Enemy.MS_Matrix = M_Enemy.MS_TranslationMatrix;

}

// 描画処理はここに
void C_Enemy1_MainGame::Draw()
{
	// 描画情報を伝える
	SHADER.m_spriteShader.SetMatrix(M_Enemy.MS_Matrix);
	// 描画処理
	SHADER.m_spriteShader.DrawColorTex(&M_Enemy.MS_Texture, M_Enemy.MS_Rectangle, M_Enemy.MS_Color_Normal);
}

// デバッグ画面に表示させたいものはここに
void C_Enemy1_MainGame::ImGuiUpdate()
{
}

// このクラスの実体が削除された時に行う領域解放処理。
void C_Enemy1_MainGame::Release()
{
	// 画像を入れている領域を解放する。
	M_Enemy.MS_Texture.Release();
}
