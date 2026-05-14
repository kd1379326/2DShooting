#include "BulletAbove_MainCharacter.h"

// Sceneクラスのヘッダー
#include "../../../../../Scene.h"

// ランダム値をくれるヘッダー
#include "../../../../../Tool/RandomNumericalValue.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_BulletAbove_MainCharacter::C_BulletAbove_MainCharacter()
{
	
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_BulletAbove_MainCharacter::~C_BulletAbove_MainCharacter()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化内容はここに
void C_BulletAbove_MainCharacter::Init(Math::Vector2 A_Position, bool AF_Turning)
{
	// 画像のパス(在処)を伝える
	M_Entity.MS_Texture.Load("Texture/Blue Effect Bullet Impact Explosion 32x32.png");

	M_FinishSlide = 0;

	// 画面サイズをSceneクラスから引っ張ってきて、ランダム値を返す関数の引数に置く。
	M_Entity.MS_Position = A_Position;
	// 移動量
	M_Entity.MS_Move = { 0, 0 };
	// 移動速度
	M_Entity.MS_MoveSpeed = { 20, 20 };
	if (!AF_Turning == C_EntityBase_MainGame::E_BulletKind::ME_Above) { M_Entity.MS_MoveSpeed = { 15, 15 }; }
	else { M_Entity.MS_MoveSpeed = { -20, -20 }; }
	// 画像の通常時の色(設定なし)
	M_Entity.MS_Color_Normal = { 1, 1, 1, 1 };
	// 半径のサイズ
	M_Entity.MS_Radius = { 16, 16 };
	// 残りの硬直時間
	M_Entity.MS_DamageStiffness_RemainingTime = 0;
	// 硬直時間(秒×フレーム)
	M_Entity.MS_DamageStiffness_Time = 1.5f * 60;
	// 攻撃の吹っ飛ばし力
	M_Entity.MS_KnockbackPower = 10;
	// テクスチャの角度
	M_Entity.MS_Rotate = 0;
	// アニメカウント
	M_Entity.MS_RectangleX = 0;
	M_Entity.MS_DeathRectangleX = 0;
	// 死亡時のアニメカウント
	M_Entity.MS_DeathCount = 0;
	// 体力
	M_Entity.MS_HP = 1;
	// 攻撃力
	M_Entity.MS_Power = 1;
	// 生存している状態にする
	M_Entity.MSF_Alive = true;
	// まだ処理が残っているという情報を持たせる
	M_Entity.MSF_Delete = false;
	// 何もされていないので硬直無しにする
	M_Entity.MSF_DamageStiffness = false;
	// 最初は誰とも接触していないのでノックバックも無し
	M_Entity.MSF_Knockback = false;
}

// 操作関連の更新内容はここに
void C_BulletAbove_MainCharacter::Action()
{
	// 上に飛ばす処理
	// 移動量に移動速度を入れ、移動量を基に座標を更新させる。
	if (M_Entity.MSF_Alive)
	{
		M_Entity.MS_Move.x = M_Entity.MS_MoveSpeed.x;
		M_Entity.MS_Position.x += M_Entity.MS_Move.x;
	}
	else
	{
		M_Entity.MS_Move.x = 3;
		M_Entity.MS_Position.x -= M_Entity.MS_Move.x;
	}

	// 弾が画面端＋半径を超えて見えなくなったらインスタンスを削除する。
	if (M_Entity.MS_Position.y >= (SCENE.Getter_ScreenSize_Top() + M_Entity.MS_Radius.y)) { M_Entity.MSF_Delete = true; }
	if (M_Entity.MS_Position.x <= (SCENE.Getter_ScreenSize_Left() - M_Entity.MS_Radius.x)) { M_Entity.MSF_Delete = true; }
	if (M_Entity.MS_Position.y <= (SCENE.Getter_ScreenSize_Bottom() - M_Entity.MS_Radius.y)) { M_Entity.MSF_Delete = true; }
	if (M_Entity.MS_Position.x >= (SCENE.Getter_ScreenSize_Right() + M_Entity.MS_Radius.x)) { M_Entity.MSF_Delete = true; }
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_BulletAbove_MainCharacter::Update()
{
	// 体力が0になったらやられた判定にする。
	if (M_Entity.MS_HP <= 0) { M_Entity.MSF_Alive = false; }

	if (SCENE.Getter_MainCharaDelete() || (SCENE.Getter_EnemyAliveNum() <= 0)) { M_FinishSlide = -30; }
	M_Entity.MS_Position.x += M_FinishSlide;

	if (M_Entity.MSF_Alive)
	{
		// イラストを傾ける
		M_Entity.MS_RotateMatrix = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(M_Entity.MS_Rotate));
		// どこに描画するか座標情報を設定する。
		M_Entity.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Entity.MS_Position.x, M_Entity.MS_Position.y, 0);

		// それぞれの描画情報を行列にまとめる
		M_Entity.MS_Matrix = M_Entity.MS_RotateMatrix * M_Entity.MS_TranslationMatrix;
	}
	if (!M_Entity.MSF_Alive)
	{
		M_Entity.MS_ScaleMatrix = Math::Matrix::CreateScale(2.5f);
		// イラストを傾ける
		M_Entity.MS_RotateMatrix = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(M_Entity.MS_Rotate));
		// どこに描画するか座標情報を設定する。
		M_Entity.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Entity.MS_Position.x, M_Entity.MS_Position.y, 0);

		// それぞれの描画情報を行列にまとめる
		M_Entity.MS_Matrix = M_Entity.MS_ScaleMatrix * M_Entity.MS_RotateMatrix * M_Entity.MS_TranslationMatrix;
	}


	if (M_Entity.MSF_Alive) { M_Entity.MS_Rotate += 4; }
	else { M_Entity.MS_Rotate = 0; }

	if (M_Entity.MS_Rotate > 360) { M_Entity.MS_Rotate = 0; }

	// やられた場合、削除フラグを立てる。
	if (!M_Entity.MSF_Alive && (M_Entity.MS_DeathCount >= 2.9f))
	{
		M_Entity.MSF_Delete = true;
	}
}

// 描画処理はここに
void C_BulletAbove_MainCharacter::Draw()
{
	// 描画情報を伝える
	SHADER.m_spriteShader.SetMatrix(M_Entity.MS_Matrix);

	// 画像の切り取り範囲(生存時)
	if (M_Entity.MSF_Alive)
	{
		M_Entity.MS_RectangleX += 0.2f;
		if (M_Entity.MS_RectangleX >= 4) { M_Entity.MS_RectangleX = 0; }

		int AnimeRect[4] = { 0, 32, 64, 32 };
		M_Entity.MS_Rectangle = { (32 * 2) + AnimeRect[(int)M_Entity.MS_RectangleX], (32 * 12 + 16), 32, 32 };
	}
	else if (!M_Entity.MSF_Delete)
	{
		
		M_Entity.MS_DeathCount += 0.2f;
		if (M_Entity.MS_DeathCount > 2.9f) { M_Entity.MS_DeathCount = 2.9f; }

		int AnimeRect[3] = { 0, 32, 64 };
		M_Entity.MS_Rectangle = { (32 * 6) + AnimeRect[(int)M_Entity.MS_DeathCount], (32 * 7), 32, 32 };
	}

	// 描画処理
	SHADER.m_spriteShader.DrawColorTex(&M_Entity.MS_Texture, M_Entity.MS_Rectangle, M_Entity.MS_Color_Normal);
}

// デバッグ画面に表示させたいものはここに
void C_BulletAbove_MainCharacter::ImGuiUpdate()
{

}

// このクラスの実体が削除された時に行う領域解放処理。
void C_BulletAbove_MainCharacter::Release()
{
	// 画像を入れている領域を解放する。
	M_Entity.MS_Texture.Release();
}
