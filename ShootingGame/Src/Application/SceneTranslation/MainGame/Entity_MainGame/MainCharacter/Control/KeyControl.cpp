#include "KeyControl.h"

#include "../../../../../Scene.h"

#include "../MainCharacter.h"

// このクラスが生成された時に動かしたい機能はここに
C_MainCharacter_KeyControl::C_MainCharacter_KeyControl()
{
}

// このクラスが削除された時に動かしたい機能はここに
C_MainCharacter_KeyControl::~C_MainCharacter_KeyControl()
{
}

void C_MainCharacter_KeyControl::Update()
{
	// クールタイムが発生した時にのみ減らしていく。
	if (M_NowCoolTime > 0) { M_NowCoolTime -= 1; }
}

// キー入力による操作機能
void C_MainCharacter_KeyControl::MoveKeyControl(Math::Vector2& A_Position, Math::Vector2& A_Move, Math::Vector2& A_MoveSpeed, Math::Vector2& A_Radius)
{
	// WASDと矢印キーどちらも同じ結果にさせる。
	if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000))      { A_Move.y =  1; }
	if ((GetAsyncKeyState('A') & 0x8000)  || (GetAsyncKeyState(VK_LEFT) & 0x8000))   { A_Move.x = -1; }
	if ((GetAsyncKeyState('S') & 0x8000)  || (GetAsyncKeyState(VK_DOWN) & 0x8000)) { A_Move.y = -1; }
	if ((GetAsyncKeyState('D') & 0x8000)  || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) { A_Move.x =  1; }

	// 斜め移動のスピードがA_Moveよりも高い数値になる為、無理やり一方に進む速さと同じ値にする。(正規化)
	A_Move.Normalize();
	// 移動量を座標に反映させる。
	A_Position += A_Move * A_MoveSpeed;
	// 反映させたらキーを離した時に止まるよう0初期化させる。
	A_Move = { 0, 0 };


}

// エンターキーが押されたときに弾を放って良いと合図する
int C_MainCharacter_KeyControl::ShootingPermission(bool& AF_Turning)
{
	if (M_NowCoolTime <= 0)
	{
		// キーが押されたら弾を撃つ許可を出し、押されていなければ許可しない。
		if (GetAsyncKeyState('X') & 0x8000)
		{ 
			M_NowCoolTime = M_CoolTime; 
			AF_Turning = false;
			return C_EntityBase_MainGame::E_BulletKind::ME_Above; 
		}
		else if (GetAsyncKeyState('Z') & 0x8000)	
		{ 
			M_NowCoolTime = M_CoolTime; 
			AF_Turning = true;
			return C_EntityBase_MainGame::E_BulletKind::ME_Above; 
		}
		else																{ return C_EntityBase_MainGame::E_BulletKind::ME_None; }
	}
	// クールタイムが終わっていなけらば無条件で許可無し。
	else { return C_EntityBase_MainGame::E_BulletKind::ME_None; }
}