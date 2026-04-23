#include "Bullet.h"

// Sceneクラスのヘッダー
#include "../../../../Scene.h"

// ランダム値をくれるヘッダー
#include "../../../../Tool/RandomNumericalValue.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_Bullet_MainGame::C_Bullet_MainGame()
{
	//// 初期座標はメインキャラに合わせる。
	//M_Bullet.MS_Position = A_MainCharacterPosition;
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_Bullet_MainGame::~C_Bullet_MainGame()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化内容はここに
void C_Bullet_MainGame::Init()
{
	// 画像のパス(在処)を伝える
	M_Bullet.MS_Texture.Load("Texture/Star/StarLight.png");

	// 画面サイズをSceneクラスから引っ張ってきて、ランダム値を返す関数の引数に置く。
	M_Bullet.MS_Position.x = (float)C_RandomNumericalValue::GetInstance().RandomNumericalValue(Scene::GetInstance().Getter_ScreenSize_Right(), Scene::GetInstance().Getter_ScreenSize_Left());
	M_Bullet.MS_Position.y = (float)C_RandomNumericalValue::GetInstance().RandomNumericalValue(Scene::GetInstance().Getter_ScreenSize_Top(), Scene::GetInstance().Getter_ScreenSize_Bottom());
	// 移動量
	M_Bullet.MS_Move = { 0, 0 };
	// 画像の切り取り範囲
	M_Bullet.MS_Rectangle = { 0, 0, 64, 64 };
	// 画像の通常時の色(設定なし)
	M_Bullet.MS_Color_Normal = { 1, 1, 1, 1 };
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_Bullet_MainGame::Update()
{
	// どこに描画するか座標情報を設定する。
	M_Bullet.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Bullet.MS_Position.x, M_Bullet.MS_Position.y, 0);

	// それぞれの描画情報を行列にまとめる
	M_Bullet.MS_Matrix = M_Bullet.MS_TranslationMatrix;

}

// 描画処理はここに
void C_Bullet_MainGame::Draw()
{
	// 描画情報を伝える
	SHADER.m_spriteShader.SetMatrix(M_Bullet.MS_Matrix);
	// 描画処理
	SHADER.m_spriteShader.DrawColorTex(&M_Bullet.MS_Texture, M_Bullet.MS_Rectangle, M_Bullet.MS_Color_Normal);
}

// デバッグ画面に表示させたいものはここに
void C_Bullet_MainGame::ImGuiUpdate()
{

}

// このクラスの実体が削除された時に行う領域解放処理。
void C_Bullet_MainGame::Release()
{
	// 画像を入れている領域を解放する。
	M_Bullet.MS_Texture.Release();
}
