#include "MainCharacter.h"

// 操作関連のクラス
#include "Control/KeyControl.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_MainCharacter_MainGame::C_MainCharacter_MainGame()
{
	M_Entity.MS_Texture.Load("Texture/MainCharacter/MainCharacter.png");
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_MainCharacter_MainGame::~C_MainCharacter_MainGame()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化内容はここに
void C_MainCharacter_MainGame::Init(Math::Vector2 A_Position)
{
	// 座標
		M_Entity.MS_Position = { -500, 0 };
	// 移動速度
		M_Entity.MS_MoveSpeed = { 15, 15 };
	// 移動量
		M_Entity.MS_Move = { 0, 0 };
	// 半径
		M_Entity.MS_Radius = { 32, 32 };
	// 画像の切り取り範囲
		M_Entity.MS_Rectangle = { 0, 0, 64, 64 };
	// 通常時の色
		M_Entity.MS_Color_Normal = { 1, 1, 1, 1.0f };
	// 残りの硬直時間
		M_Entity.MS_DamageStiffness_RemainingTime = 0;
	// 硬直時間(秒×フレーム)
		M_Entity.MS_DamageStiffness_Time = 1 * 60;
	// 攻撃の吹っ飛ばし力
		M_Entity.MS_KnockbackPower = 20;
	// 体力
		M_Entity.MS_HP = 3;
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

	// キー操作の機能が入ったクラスの実体を作成
	CM_Control = std::make_shared<C_MainCharacter_KeyControl>();
	
}

// 操作関連の更新内容はここに
void C_MainCharacter_MainGame::Action()
{
	// ノックバック中は操作不能にする。
	if (!M_Entity.MSF_Knockback)
	{
		// キー操作による移動機能
		CM_Control->MoveKeyControl(M_Entity.MS_Position, M_Entity.MS_Move, M_Entity.MS_MoveSpeed, M_Entity.MS_Radius);
	}
	// ノックバック処理
	if (M_Entity.MSF_Knockback)
	{
		// ノックバックさせたい(ノックバックする値が0じゃない)時のみ通す。
		if (M_NowKnockback != 0)
		{
			// 現在の座標からノックバックしたい距離を計算する。
			M_Entity.MS_Position.x += M_NowKnockback;
			// ノックバックの距離を縮めていく。
			M_NowKnockback *= M_Knockback_Subtract;
			// ノックバックの値がある程度小さくなったら強制的に0にする。
			if (M_NowKnockback > M_Knockback_Minimum) { M_NowKnockback = 0; }
		}
		else
		{
			// ノックバックさせ終えたらノックバックしないと伝える。
			M_Entity.MSF_Knockback = false;
		}
	}
	else
	{
		// ノックバック処理が終わった後にノックバックさせたい距離を代入する。
		M_NowKnockback = M_KnockbackDistance;
	}
}

// 更新内容はここに
void C_MainCharacter_MainGame::Update()
{
	// キー操作クラスの更新処理
	CM_Control->Update();



	// 体力が0になったらやられた判定にする。
	if (M_Entity.MS_HP <= 0) { M_Entity.MSF_Alive = false; }

	// やられた場合、削除フラグを立てる。
	if (!M_Entity.MSF_Alive) { M_Entity.MSF_Delete = true; }

	// 表示したい座標を設定する
	M_Entity.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Entity.MS_Position.x, M_Entity.MS_Position.y, 0);

	// 描画の詳細をまとめる
	M_Entity.MS_Matrix = M_Entity.MS_TranslationMatrix;
}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_MainCharacter_MainGame::Draw()
{
	SHADER.m_spriteShader.SetMatrix(M_Entity.MS_Matrix);
	SHADER.m_spriteShader.DrawColorTex(&M_Entity.MS_Texture, M_Entity.MS_Rectangle, M_Entity.MS_Color_Normal);
}

// デバッグ画面に出したい内容はここに
void C_MainCharacter_MainGame::ImGuiUpdate()
{

}

// 弾を撃つかどうか判断する
bool C_MainCharacter_MainGame::ShootBullet()
{
	// 射撃用のクールタイムが無い且つエンターキーが押されたらtrueが返される。
	return CM_Control->ShootingPermission();
}

// このクラスの実体が削除された時に行う領域解放処理。
void C_MainCharacter_MainGame::Release()
{
	// 画像を入れている領域を解放する。
	M_Entity.MS_Texture.Release();
}