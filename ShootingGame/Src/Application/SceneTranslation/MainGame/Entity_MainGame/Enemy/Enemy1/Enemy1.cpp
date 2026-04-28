#include "Enemy1.h"

// Sceneクラスのヘッダー
#include "../../../../../Scene.h"

// ランダム値をくれるヘッダー
#include "../../../../../Tool/RandomNumericalValue.h"

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
		M_Entity.MS_Texture.Load("Texture/Star/StarShadow.png");
	// 半径のサイズ
		M_Entity.MS_Radius = { 32, 32 };

	// 座標(1280×720の範囲で出現させる)
	// 画面サイズをSceneクラスから引っ張ってきて、半径分をも含めた値をランダム値を返す関数の引数に置く。
	// 画面内に全身が納まる位置で出現させる。
		M_Entity.MS_Position.x = (float)C_RandomNumericalValue::GetInstance().RandomNumericalValue((Scene::GetInstance().Getter_ScreenSize_Right() - M_Entity.MS_Radius.x), (Scene::GetInstance().Getter_ScreenSize_Left()       + M_Entity.MS_Radius.x));
		M_Entity.MS_Position.y = (float)C_RandomNumericalValue::GetInstance().RandomNumericalValue((Scene::GetInstance().Getter_ScreenSize_Top()    - M_Entity.MS_Radius.y), (Scene::GetInstance().Getter_ScreenSize_Bottom() + M_Entity.MS_Radius.y));
	// 移動量
		M_Entity.MS_Move = { 0, 0 };
	// 画像の切り取り範囲
		M_Entity.MS_Rectangle = { 0, 0, 64, 64 };
	// 画像の通常時の色(設定なし)
		M_Entity.MS_Color_Normal = { 1, 1, 1, 1 };
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_Enemy1_MainGame::Update()
{
	// どこに描画するか座標情報を設定する。
	M_Entity.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Entity.MS_Position.x, M_Entity.MS_Position.y, 0);

	// それぞれの描画情報を行列にまとめる
	M_Entity.MS_Matrix = M_Entity.MS_TranslationMatrix;

}

// 描画処理はここに
void C_Enemy1_MainGame::Draw()
{
	// 描画情報を伝える
	SHADER.m_spriteShader.SetMatrix(M_Entity.MS_Matrix);
	// 描画処理
	SHADER.m_spriteShader.DrawColorTex(&M_Entity.MS_Texture, M_Entity.MS_Rectangle, M_Entity.MS_Color_Normal);
}

// デバッグ画面に表示させたいものはここに
void C_Enemy1_MainGame::ImGuiUpdate()
{
	ImGui::Text(u8"敵の座標：X-%.0f｜Y-%.0f", M_Entity.MS_Position.x, M_Entity.MS_Position.y);
}

// 弾を撃つかどうか判断する
bool C_Enemy1_MainGame::ShootBullet()
{
	return false;
}

// このクラスの実体が削除された時に行う領域解放処理。
void C_Enemy1_MainGame::Release()
{
	// 画像を入れている領域を解放する。
	M_Entity.MS_Texture.Release();
}
