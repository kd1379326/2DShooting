#include "Enemy1_Move.h"

// ランダム値を返してくれるクラス
#include "../../../../../../Tool/RandomNumericalValue.h"

// 画面サイズを持ってくるため
#include "../../../../../../Scene.h"

// このクラスが生成された時に動かしたいものをここに(コンストラクタ)
C_Enemy1_Move::C_Enemy1_Move()
{

}

// このクラスが削除される時に動かしたいものをここに(デストラクタ)
C_Enemy1_Move::~C_Enemy1_Move()
{
	// 自動で領域解放処理を行う。
	Release();
}

// 初期化処理
void C_Enemy1_Move::Init(C_EntityBase_MainGame::S_EntityCharacter& A_Entity)
{
	// 出現後、前に出る座標。
	M_StopPosition = C_RandomNumericalValue::Instance().RandomNumericalValue((Scene::Instance().Getter_ScreenSize_Left() + A_Entity.MS_Radius.x), -550);
}

// 更新内容
void C_Enemy1_Move::Action(C_EntityBase_MainGame::S_EntityCharacter& A_Entity)
{
	// 弾発射許可の処理
	ShootingPermission();

	// 移動処理
	Move(A_Entity);

	// クールタイムが発生した時にのみ減らしていく。
	if (M_NowShootingCoolTime > 0) { M_NowShootingCoolTime -= 1; }
}

// 解放処理
void C_Enemy1_Move::Release()
{

}

// クールタイムが無くなれば弾を発射する
bool C_Enemy1_Move::ShootingPermission()
{
	if (M_NowShootingCoolTime <= 0)
	{
		// クールタイムをリセット
		M_NowShootingCoolTime = M_ShootingCoolTime; 
		return true;
	}
	// クールタイムが終わっていなけらば無条件で許可無し。
	else { return false; }
}

// 移動処理
void C_Enemy1_Move::Move(C_EntityBase_MainGame::S_EntityCharacter& A_Entity)
{
	// 旋回するタイミングは左端を完全に通り過ぎた時
	// 条件１：左端を通り過ぎる(画面左端+半径分)
	// 条件２：旋回フラグが立っていない
	if ((A_Entity.MS_Position.x < (Scene::Instance().Getter_ScreenSize_Left() - A_Entity.MS_Radius.x)) && !MF_TurningFlag) { MF_TurningFlag = true; }

	// 直線移動
	if (!MF_TurningFlag)	{ A_Entity.MS_Move =  A_Entity.MS_MoveSpeed; }
	else					{ A_Entity.MS_Move = -A_Entity.MS_MoveSpeed; }
	A_Entity.MS_Position.x -= A_Entity.MS_Move.x;

	// ノックバック処理
	if (A_Entity.MSF_Knockback)
	{
		// ノックバックさせたい(ノックバックする値が0じゃない)時のみ通す。
		if (M_NowKnockback > 0)
		{
			// 現在の座標からノックバックしたい距離を計算する。
			A_Entity.MS_Position.x += M_NowKnockback;
			// ノックバックの距離を縮めていく。
			M_NowKnockback *= M_Knockback_Subtract;
			// ノックバックの値がある程度小さくなったら強制的に0にする。
			if (M_NowKnockback < M_Knockback_Minimum) { M_NowKnockback = 0; }
		}
		else
		{
			// ノックバックさせ終えたらノックバックしないと伝える。
			A_Entity.MSF_Knockback = false;
		}
	}
	else
	{
		// ノックバック処理が終わった後にノックバックさせたい距離を代入する。
		M_NowKnockback = M_KnockbackDistance;
	}

	// 前に出てくる座標
	// 条件１：X座標が指定の座標を越える
	// 条件２：旋回する場合
	if ((A_Entity.MS_Position.x > M_StopPosition) && MF_TurningFlag) { A_Entity.MS_Position.x -= 10; }
}