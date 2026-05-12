#include "MainCharacter.h"

// 操作関連のクラス
#include "Control/KeyControl.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_MainCharacter_MainGame::C_MainCharacter_MainGame()
{
	M_Entity.MS_Texture.Load("Texture/MainCharacter/MainCharacter仮.png");
	M_Explosion_Damage.MS_Texture.Load("Texture/Red Effect Bullet Impact Explosion 32x32.png");
	M_Smoke.MS_Texture.Load("Texture/Red Effect Bullet Impact Explosion 32x32.png");
	M_Explosion_Death.MS_Texture.Load("Texture/Red Effect Bullet Impact Explosion 32x32.png");
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_MainCharacter_MainGame::~C_MainCharacter_MainGame()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化内容はここに
void C_MainCharacter_MainGame::Init(Math::Vector2 A_Position, bool AF_Turning)
{
	// M_Entity
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
		M_Entity.MS_Rectangle = { 0, 0, 50, 50 };
		// 通常時の色
		M_Entity.MS_Color_Normal = { 1, 1, 1, 1.0f };
		// 残りの硬直時間
		M_Entity.MS_DamageStiffness_RemainingTime = 0;
		// 硬直時間(秒×フレーム)
		M_Entity.MS_DamageStiffness_Time = 1 * 60;
		// 攻撃の吹っ飛ばし力
		M_Entity.MS_KnockbackPower = 20;
		// 画像のサイズ
		M_Entity.MS_NormalSize = 1.0f;
		// アニメーション用
		M_Entity.MS_RectangleX = 0;
		M_Entity.MS_DeathRectangleX = 0;
		// 死亡時のアニメーションカウント
		M_Entity.MS_DeathCount = 0;
		// 体力
		M_Entity.MS_HP = 3;
		// 攻撃力
		M_Entity.MS_Power = 2;
		// 生存している状態にする
		M_Entity.MSF_Alive = true;
		// まだ処理が残っているという情報を持たせる
		M_Entity.MSF_Delete = false;
		// 何もされていないので硬直無しにする
		M_Entity.MSF_DamageStiffness = false;
		// 最初は誰とも接触していないのでノックバックも無し
		M_Entity.MSF_Knockback = false;
		// 始めは旋回していない
		M_Entity.MSF_TurningFlag = false;
		M_Entity.MSF_OpponentTurningFlag = false;
		// ダメージは受けていない
		M_Entity.MSF_Damage = false;
	}

	// M_Explosion_Damage
	{
		// 座標
		M_Explosion_Damage.MS_Position = { -500, 0 };
		// 移動速度
		M_Explosion_Damage.MS_MoveSpeed = { 15, 15 };
		// 移動量
		M_Explosion_Damage.MS_Move = { 0, 0 };
		// 半径
		M_Explosion_Damage.MS_Radius = { 16, 16 };
		// 通常時の色
		M_Explosion_Damage.MS_Color_Normal = { 1, 1, 1, 1.0f };
		// 残りの硬直時間
		M_Explosion_Damage.MS_DamageStiffness_RemainingTime = 0;
		// 硬直時間(秒×フレーム)
		M_Explosion_Damage.MS_DamageStiffness_Time = 1 * 60;
		// 攻撃の吹っ飛ばし力
		M_Explosion_Damage.MS_KnockbackPower = 20;
		// 画像のサイズ
		M_Explosion_Damage.MS_NormalSize = 2.0f;
		// アニメーション用
		M_Explosion_Damage.MS_RectangleX = 0;
		M_Explosion_Damage.MS_DeathRectangleX = 0;
		// 死亡時のアニメーションカウント
		M_Explosion_Damage.MS_DeathCount = 0;
		// 体力
		M_Explosion_Damage.MS_HP = 10;
		// 攻撃力
		M_Explosion_Damage.MS_Power = 2;
		// 生存している状態にする
		M_Explosion_Damage.MSF_Alive = false;
		// まだ処理が残っているという情報を持たせる
		M_Explosion_Damage.MSF_Delete = false;
		// 何もされていないので硬直無しにする
		M_Explosion_Damage.MSF_DamageStiffness = false;
		// 最初は誰とも接触していないのでノックバックも無し
		M_Explosion_Damage.MSF_Knockback = false;
		// 始めは旋回していない
		M_Explosion_Damage.MSF_TurningFlag = false;
		M_Explosion_Damage.MSF_OpponentTurningFlag = false;
		// ダメージを受けたか
		M_Explosion_Damage.MSF_Damage = false;
	}

	// M_Explosion_Death
	{
		// 座標
		M_Explosion_Death.MS_Position = { -500, 0 };
		// 移動速度
		M_Explosion_Death.MS_MoveSpeed = { 15, 15 };
		// 移動量
		M_Explosion_Death.MS_Move = { 0, 0 };
		// 半径
		M_Explosion_Death.MS_Radius = { 16, 16 };
		// 通常時の色
		M_Explosion_Death.MS_Color_Normal = { 1, 1, 1, 1.0f };
		// 残りの硬直時間
		M_Explosion_Death.MS_DamageStiffness_RemainingTime = 0;
		// 硬直時間(秒×フレーム)
		M_Explosion_Death.MS_DamageStiffness_Time = 1 * 60;
		// 攻撃の吹っ飛ばし力
		M_Explosion_Death.MS_KnockbackPower = 20;
		// 画像のサイズ
		M_Explosion_Death.MS_NormalSize = 5.0f;
		// アニメーション用
		M_Explosion_Death.MS_RectangleX = 0;
		M_Explosion_Death.MS_DeathRectangleX = 0;
		// 死亡時のアニメーションカウント
		M_Explosion_Death.MS_DeathCount = 0;
		// 体力
		M_Explosion_Death.MS_HP = 10;
		// 攻撃力
		M_Explosion_Death.MS_Power = 2;
		// 生存している状態にする
		M_Explosion_Death.MSF_Alive = false;
		// まだ処理が残っているという情報を持たせる
		M_Explosion_Death.MSF_Delete = false;
		// 何もされていないので硬直無しにする
		M_Explosion_Death.MSF_DamageStiffness = false;
		// 最初は誰とも接触していないのでノックバックも無し
		M_Explosion_Death.MSF_Knockback = false;
		// 始めは旋回していない
		M_Explosion_Death.MSF_TurningFlag = false;
		M_Explosion_Death.MSF_OpponentTurningFlag = false;
		// ダメージを受けたか
		M_Explosion_Death.MSF_Damage = false;
	}

	// M_Smoke
	{
		// 座標
		M_Smoke.MS_Position = { -500, 0 };
		// 移動速度
		M_Smoke.MS_MoveSpeed = { 15, 15 };
		// 移動量
		M_Smoke.MS_Move = { 0, 0 };
		// 半径
		M_Smoke.MS_Radius = { 16, 16 };
		// 通常時の色
		M_Smoke.MS_Color_Normal = { 1, 1, 1, 1.0f };
		// 残りの硬直時間
		M_Smoke.MS_DamageStiffness_RemainingTime = 0;
		// 硬直時間(秒×フレーム)
		M_Smoke.MS_DamageStiffness_Time = 1 * 60;
		// 攻撃の吹っ飛ばし力
		M_Smoke.MS_KnockbackPower = 20;
		// 画像のサイズ
		M_Smoke.MS_NormalSize = 5.0f;
		// アニメーション用
		M_Smoke.MS_RectangleX = 0;
		M_Smoke.MS_DeathRectangleX = 0;
		// 死亡時のアニメーションカウント
		M_Smoke.MS_DeathCount = 0;
		// 体力
		M_Smoke.MS_HP = 10;
		// 攻撃力
		M_Smoke.MS_Power = 2;
		// 生存している状態にする
		M_Smoke.MSF_Alive = false;
		// まだ処理が残っているという情報を持たせる
		M_Smoke.MSF_Delete = false;
		// 何もされていないので硬直無しにする
		M_Smoke.MSF_DamageStiffness = false;
		// 最初は誰とも接触していないのでノックバックも無し
		M_Smoke.MSF_Knockback = false;
		// 始めは旋回していない
		M_Smoke.MSF_TurningFlag = false;
		M_Smoke.MSF_OpponentTurningFlag = false;
		// ダメージを受けたか
		M_Smoke.MSF_Damage = false;
	}

	// キー操作の機能が入ったクラスの実体を作成
	CM_Control = std::make_shared<C_MainCharacter_KeyControl>();
	
}

// 操作関連の更新内容はここに
void C_MainCharacter_MainGame::Action()
{
	//// ノックバック処理
	//if (M_Entity.MSF_Knockback)
	//{
	//	// ノックバックさせたい(ノックバックする値が0じゃない)時のみ通す。
	//	if (M_NowKnockback != 0)
	//	{
	//		// 旋回していなければ左に弾かれる
	//		if (!M_Entity.MSF_OpponentTurningFlag)
	//		{
	//			// 現在の座標からノックバックしたい距離を計算する。
	//			M_Entity.MS_Position.x += M_NowKnockback;
	//			// ノックバックの距離を縮めていく。
	//			M_NowKnockback *= M_Knockback_Subtract;
	//			// ノックバックの値がある程度小さくなったら強制的に0にする。
	//			if (M_NowKnockback > M_Knockback_Minimum_Left) { M_NowKnockback = 0; }
	//		}
	//		// 旋回していれば右に弾かれる
	//		else
	//		{
	//			// 現在の座標からノックバックしたい距離を計算する。
	//			M_Entity.MS_Position.x -= M_NowKnockback;
	//			// ノックバックの距離を縮めていく。
	//			M_NowKnockback *= M_Knockback_Subtract;
	//			// ノックバックの値がある程度小さくなったら強制的に0にする。
	//			if (-M_NowKnockback < M_Knockback_Minimum_Right) { M_NowKnockback = 0; }
	//		}
	//	}
	//	else
	//	{
	//		// ノックバックさせ終えたらノックバックしないと伝える。
	//		M_Entity.MSF_Knockback = false;
	//	}
	//}
	//else
	//{
	//	// ノックバック処理が終わった後にノックバックさせたい距離を代入する。
	//	M_NowKnockback = M_KnockbackDistance;
	//}

	if (M_Entity.MSF_Alive)
	{
		// 現在座標にベクトルを足して弾くように移動させる。
		M_Entity.MS_Position += M_Entity.MS_KnockbackVector;
		// 常にベクトルを足し続けると止まらない為、徐々にベクトルを小さくしていく。
		M_Entity.MS_KnockbackVector *= 0.85f;
		// ベクトルが0になるのにかなり時間が掛かる為、一定の数値まで下がったら強制的に0にする。
		if (std::abs(M_Entity.MS_KnockbackVector.x) < 1.0f) M_Entity.MS_KnockbackVector.x = 0.0f;
		if (std::abs(M_Entity.MS_KnockbackVector.y) < 1.0f) M_Entity.MS_KnockbackVector.y = 0.0f;

		// キー操作による移動機能
		CM_Control->MoveKeyControl(M_Entity.MS_Position, M_Entity.MS_Move, M_Entity.MS_MoveSpeed, M_Entity.MS_Radius);
	}

}

// 更新内容はここに
void C_MainCharacter_MainGame::Update()
{
	// キー操作クラスの更新処理
	CM_Control->Update();

	// やられた場合、削除フラグを立てる。
	if (M_Entity.MS_DeathCount == (32 * 3.9f)) { M_Entity.MSF_Delete = true; }

	// 表示したい座標を設定する
	if (M_Entity.MSF_Alive)
	{
		M_Entity.MS_RotateMatrix = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(-90));
		M_Entity.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Entity.MS_Position.x, M_Entity.MS_Position.y, 0);
		
		// 描画の詳細をまとめる
		M_Entity.MS_Matrix = M_Entity.MS_RotateMatrix * M_Entity.MS_TranslationMatrix;
	}

	if (M_Entity.MSF_Alive && M_Entity.MSF_Damage)
	{
		M_Explosion_Damage.MS_ScaleMatrix = Math::Matrix::CreateScale(M_Explosion_Damage.MS_NormalSize);
		M_Explosion_Damage.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Entity.MS_Position.x, M_Entity.MS_Position.y, 0);
		// 描画の詳細をまとめる
		M_Explosion_Damage.MS_Matrix = M_Explosion_Damage.MS_ScaleMatrix * M_Explosion_Damage.MS_TranslationMatrix;
	}

	if (!M_Entity.MSF_Alive && !M_Entity.MSF_Delete)
	{
		M_Explosion_Death.MS_ScaleMatrix = Math::Matrix::CreateScale(M_Explosion_Death.MS_NormalSize);
		M_Explosion_Death.MS_TranslationMatrix = Math::Matrix::CreateTranslation(M_Entity.MS_Position.x, M_Entity.MS_Position.y, 0);
		// 描画の詳細をまとめる
		M_Explosion_Death.MS_Matrix = M_Explosion_Death.MS_ScaleMatrix * M_Explosion_Death.MS_TranslationMatrix;
	}


}

// 描画内容はここに(行列(Matrix等)はUpdateに含まれる)
void C_MainCharacter_MainGame::Draw()
{
	// 体力が0になったらやられた判定にする。
	if (M_Entity.MS_HP <= 0) { M_Entity.MSF_Alive = false; }

	if (M_Entity.MSF_Alive)
	{
		// 画像の切り取り範囲
		M_Explosion_Damage.MS_Rectangle = { 0, 0, 50, 50 };

		SHADER.m_spriteShader.SetMatrix(M_Entity.MS_Matrix);
		SHADER.m_spriteShader.DrawColorTex(&M_Entity.MS_Texture, M_Entity.MS_Rectangle, M_Entity.MS_Color_Normal);
	}


	if (M_Entity.MSF_Alive && M_Entity.MSF_Damage)
	{
		M_Explosion_Damage.MS_DeathCount += 5;
		if (M_Explosion_Damage.MS_DeathCount >= (32 * 3.9f)) { M_Explosion_Damage.MS_DeathCount = (32 * 3.9f); }
		// 画像の切り取り範囲
		M_Explosion_Damage.MS_Rectangle = { (32 * 16) + (32 * (int)(M_Explosion_Damage.MS_DeathCount / 32)), (32 * 11), 32, 32 };

		SHADER.m_spriteShader.SetMatrix(M_Explosion_Damage.MS_Matrix);
		SHADER.m_spriteShader.DrawColorTex(&M_Explosion_Damage.MS_Texture, M_Explosion_Damage.MS_Rectangle, M_Explosion_Damage.MS_Color_Normal);

		if (M_Explosion_Damage.MS_DeathCount >= (32 * 3.9f))
		{ 
			M_Explosion_Damage.MS_DeathCount = 0;
			M_Entity.MSF_Damage = false;
		}
	}
	
	
	if (!M_Entity.MSF_Alive && !M_Entity.MSF_Delete && M_Entity.MS_DeathCount < (32 * 3.9f))
	{
		M_Entity.MS_DeathCount += 5;
		if (M_Entity.MS_DeathCount >= (32 * 3.9f)) { M_Entity.MS_DeathCount = (32 * 3.9f); }
		// 画像の切り取り範囲
		M_Explosion_Death.MS_Rectangle = { (32 * 16) + (32 * (int)(M_Entity.MS_DeathCount / 32)), (32 * 12), 32, 32 };

		SHADER.m_spriteShader.SetMatrix(M_Explosion_Death.MS_Matrix);
		SHADER.m_spriteShader.DrawColorTex(&M_Explosion_Death.MS_Texture, M_Explosion_Death.MS_Rectangle, M_Explosion_Death.MS_Color_Normal);
	}


}

// デバッグ画面に出したい内容はここに
void C_MainCharacter_MainGame::ImGuiUpdate()
{

}

// 弾を撃つかどうか判断する
int C_MainCharacter_MainGame::ShootBullet()
{
	// 射撃用のクールタイムが無い且つエンターキーが押されたらtrueが返される。
	return CM_Control->ShootingPermission(M_Entity.MSF_TurningFlag);
}

// このクラスの実体が削除された時に行う領域解放処理。
void C_MainCharacter_MainGame::Release()
{
	// 画像を入れている領域を解放する。
	M_Entity.MS_Texture.Release();
	M_Smoke.MS_Texture.Release();
	M_Explosion_Damage.MS_Texture.Release();
	M_Explosion_Death.MS_Texture.Release();
}