#include "Bullet_Enemy1.h"

// Sceneクラスのヘッダー
#include "../../../../../Scene.h"

// ランダム値をくれるヘッダー
#include "../../../../../Tool/RandomNumericalValue.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_Bullet_Enemy1::C_Bullet_Enemy1()
{
	
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_Bullet_Enemy1::~C_Bullet_Enemy1()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化内容はここに
void C_Bullet_Enemy1::Init(Math::Vector2 A_Position)
{
	// 画像のパス(在処)を伝える
	M_Entity.MS_Texture.Load("Texture/Star/StarLight.png");

	// 画面サイズをSceneクラスから引っ張ってきて、ランダム値を返す関数の引数に置く。
	M_Entity.MS_Position = A_Position;
	// 移動量
	M_Entity.MS_Move = { 0, 0 };
	// 移動速度
	M_Entity.MS_MoveSpeed = { 20, 20 };
	// 画像の切り取り範囲
	M_Entity.MS_Rectangle = { 0, 0, 64, 64 };
	// 画像の通常時の色(設定なし)
	M_Entity.MS_Color_Normal = { 1, 1, 1, 1 };
	// 半径のサイズ
	M_Entity.MS_Radius = { 32, 32 };
	// 生存している状態にする
	M_Entity.MSF_Alive = true;
	// まだ処理が残っているという情報を持たせる
	M_Entity.MSF_Delete = false;
}

// 操作関連の更新内容はここに
void C_Bullet_Enemy1::Action()
{
	// 上に飛ばす処理
	//移動量に移動速度を入れ、移動量を基に座標を更新させる。
	M_Entity.MS_Move.x = M_Entity.MS_MoveSpeed.x;
	M_Entity.MS_Position.x += M_Entity.MS_Move.x;

	// 弾が画面端＋半径を超えて見えなくなったらインスタンスを削除する。
	if (M_Entity.MS_Position.y >= (SCENE.Getter_ScreenSize_Top() + M_Entity.MS_Radius.y)) { M_Entity.MSF_Delete = true; }
	if (M_Entity.MS_Position.x <= (SCENE.Getter_ScreenSize_Left() - M_Entity.MS_Radius.x)) { M_Entity.MSF_Delete = true; }
	if (M_Entity.MS_Position.y <= (SCENE.Getter_ScreenSize_Bottom() - M_Entity.MS_Radius.y)) { M_Entity.MSF_Delete = true; }
	if (M_Entity.MS_Position.x >= (SCENE.Getter_ScreenSize_Right() + M_Entity.MS_Radius.x)) { M_Entity.MSF_Delete = true; }
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_Bullet_Enemy1::Update()
{
	// やられた場合、削除フラグを立てる。
	if (!M_Entity.MSF_Alive) { M_Entity.MSF_Delete = true; }

	// どこに描画するか座標情報を設定する。
	M_Entity.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Entity.MS_Position.x, M_Entity.MS_Position.y, 0);

	// それぞれの描画情報を行列にまとめる
	M_Entity.MS_Matrix = M_Entity.MS_TranslationMatrix;

}

// 描画処理はここに
void C_Bullet_Enemy1::Draw()
{
	// 描画情報を伝える
	SHADER.m_spriteShader.SetMatrix(M_Entity.MS_Matrix);
	// 描画処理
	SHADER.m_spriteShader.DrawColorTex(&M_Entity.MS_Texture, M_Entity.MS_Rectangle, M_Entity.MS_Color_Normal);
}

// デバッグ画面に表示させたいものはここに
void C_Bullet_Enemy1::ImGuiUpdate()
{

}

// このクラスの実体が削除された時に行う領域解放処理。
void C_Bullet_Enemy1::Release()
{
	// 画像を入れている領域を解放する。
	M_Entity.MS_Texture.Release();
}
