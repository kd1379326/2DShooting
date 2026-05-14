#include "Boss.h"

// Sceneクラスのヘッダー
#include "../../../../../Scene.h"

// ランダム値をくれるヘッダー
#include "../../../../../Tool/RandomNumericalValue.h"

// 動作処理を行うクラス
#include "Control/Boss_Move.h"


// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_Boss_MainGame::C_Boss_MainGame()
{
}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_Boss_MainGame::~C_Boss_MainGame()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化内容はここに
void C_Boss_MainGame::Init(Math::Vector2 A_Position, bool AF_Turning)
{
	// 画像のパス(在処)を伝える
		M_Entity.MS_Texture.Load("Texture/MainCharacter/Boss.png");
		M_Explosion_Damage.MS_Texture.Load("Texture/Blue Effect Bullet Impact Explosion 32x32.png");
		M_Smoke.MS_Texture.Load("Texture/Blue Effect Bullet Impact Explosion 32x32.png");
		M_Explosion_Death.MS_Texture.Load("Texture/Blue Effect Bullet Impact Explosion 32x32.png");
	// 半径のサイズ
		M_Entity.MS_Radius = { 32, 32 };

		// M_Entity
		{
			// 座標(1280×720の範囲で出現させる)
			// 画面サイズをSceneクラスから引っ張ってきて、半径分をも含めた値をランダム値を返す関数の引数に置く。
			// 画面右端の見えない位置で上下は画面内に納まる座標をランダムに取り出す。
			M_Entity.MS_Position.x = ((float)Scene::Instance().Getter_ScreenSize_Right() + M_Entity.MS_Radius.x);
			M_Entity.MS_Position.y = (float)C_RandomNumericalValue::Instance().RandomNumericalValue((Scene::Instance().Getter_ScreenSize_Top() - M_Entity.MS_Radius.y), (Scene::Instance().Getter_ScreenSize_Bottom() + M_Entity.MS_Radius.y));
			// 移動量
			M_Entity.MS_Move = { 0, 0 };
			// 移動スピード
			M_Entity.MS_MoveSpeed = { 3, 3 };
			// 画像の切り取り範囲
			M_Entity.MS_Rectangle = { 0, 0, 111, 128 };
			// 画像の通常時の色(設定なし)
			M_Entity.MS_Color_Normal = { 1, 0, 0, 1 };
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
			// 角度
			M_Entity.MS_Rotate = 90;
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
			// 始めは旋回しない
			M_Entity.MSF_TurningFlag = false;
			// ダメージを受けたか
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

	// 操作処理を行うクラスのインスタンスを作成
		if (!CMP_Control) { CMP_Control = std::make_shared<C_Boss_Move>(); }
	// C_Boss_Moveの初期化
		CMP_Control->Init(M_Entity);
}

// 操作関連の更新内容はここに
void C_Boss_MainGame::Action()
{
	// ノックバック中は操作不能にする。
	//if (!M_Entity.MSF_Knockback)
	{
		CMP_Control->Action(M_Entity);
	}
}

// 更新内容はここに(描画に使うMatrix(行列)の作成や画像の指定もここ)
void C_Boss_MainGame::Update()
{

	// やられた場合、削除フラグを立てる。
	if (M_Entity.MS_DeathCount == (32 * 3.9f)) { M_Entity.MSF_Delete = true; }
	// 左端を超えたらもう画面内には戻らないので削除許可を出す。
	//if (M_Entity.MS_Position.x < (Scene::Instance().Getter_ScreenSize_Left() - M_Entity.MS_Radius.x)) { M_Entity.MSF_Delete = true; }

	if (M_Entity.MSF_Alive)
	{
		// 現在座標にベクトルを足して弾くように移動させる。
		M_Entity.MS_Position += M_Entity.MS_KnockbackVector;

		// 常にベクトルを足し続けると止まらない為、徐々にベクトルを小さくしていく。
		M_Entity.MS_KnockbackVector *= 0.85f;

		// ベクトルが0になるのにかなり時間が掛かる為、一定の数値まで下がったら強制的に0にする。
		if (std::abs(M_Entity.MS_KnockbackVector.x) < 1.0f) M_Entity.MS_KnockbackVector.x = 0.0f;
		if (std::abs(M_Entity.MS_KnockbackVector.y) < 1.0f) M_Entity.MS_KnockbackVector.y = 0.0f;
	}





	// 旋回する場合は反転させる
	if (M_Entity.MSF_TurningFlag) { M_Entity.MS_Rotate = -90; }


	if (M_Entity.MSF_Alive)
	{
		// どこに描画するか座標情報を設定する。
		M_Entity.MS_RotateMatrix = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(M_Entity.MS_Rotate));
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

// 描画処理はここに
void C_Boss_MainGame::Draw()
{
	// 体力が0になったらやられた判定にする。
	if (M_Entity.MS_HP <= 0) { M_Entity.MSF_Alive = false; }

	if (M_Entity.MSF_Alive)
	{
		// 描画情報を伝える
		KdShaderManager::GetInstance().m_spriteShader.SetMatrix(M_Entity.MS_Matrix);
		// 描画処理
		KdShaderManager::GetInstance().m_spriteShader.DrawColorTex(&M_Entity.MS_Texture, M_Entity.MS_Rectangle, M_Entity.MS_Color_Normal);
	}

	if (M_Entity.MSF_Alive && M_Entity.MSF_Damage)
	{
		M_Explosion_Damage.MS_DeathCount += 5;
		if (M_Explosion_Damage.MS_DeathCount >= (111 * 3.9f)) { M_Explosion_Damage.MS_DeathCount = (111 * 3.9f); }
		// 画像の切り取り範囲
		M_Explosion_Damage.MS_Rectangle = { (111 * 16) + (111 * (int)(M_Explosion_Damage.MS_DeathCount / 111)), (111 * 11), 111, 111 };

		SHADER.m_spriteShader.SetMatrix(M_Explosion_Damage.MS_Matrix);
		SHADER.m_spriteShader.DrawColorTex(&M_Explosion_Damage.MS_Texture, M_Explosion_Damage.MS_Rectangle, M_Explosion_Damage.MS_Color_Normal);

		if (M_Explosion_Damage.MS_DeathCount >= (111 * 3.9f))
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

// デバッグ画面に表示させたいものはここに
void C_Boss_MainGame::ImGuiUpdate()
{
	ImGui::Text(u8"敵の座標：X-%.0f｜Y-%.0f", M_Entity.MS_Position.x, M_Entity.MS_Position.y);
}

// 弾を撃つかどうか判断する
int C_Boss_MainGame::ShootBullet()
{
	// 射撃用のクールタイムが無い且つエンターキーが押されたらtrueが返される。
	return CMP_Control->ShootingPermission(M_Entity.MSF_Alive);
}

// このクラスの実体が削除された時に行う領域解放処理。
void C_Boss_MainGame::Release()
{
	// 画像を入れている領域を解放する。
	M_Entity.MS_Texture.Release();
	M_Smoke.MS_Texture.Release();
	M_Explosion_Damage.MS_Texture.Release();
	M_Explosion_Death.MS_Texture.Release();
}

// 旋回フラグ
bool C_Boss_MainGame::Getter_TurningFlag() { return CMP_Control->Getter_TurningFlag(); }