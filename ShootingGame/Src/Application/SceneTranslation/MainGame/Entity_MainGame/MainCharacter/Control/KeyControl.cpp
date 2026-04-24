#include "KeyControl.h"

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
	if (M_NowCoolTime > 0) { M_NowCoolTime--; }
}

// キー入力による操作機能
void C_MainCharacter_KeyControl::MoveKeyControl(Math::Vector2& A_Position, Math::Vector2& A_Move)
{
	// WASDと矢印キーどちらも同じ結果にさせる。
	if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000)) { A_Position.y += A_Move.y; }
	if ((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000)) { A_Position.x -= A_Move.x; }
	if ((GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000)) { A_Position.y -= A_Move.y; }
	if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) { A_Position.x += A_Move.x; }
}

// エンターキーが押されたときに弾を放って良いと合図する
bool C_MainCharacter_KeyControl::ShootingPermission()
{
	if (M_NowCoolTime <= 0)
	{
		// キーが押されたら弾を撃つ許可を出し、押されていなければ許可しない。
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)	{ M_NowCoolTime = M_CoolTime; return true; }
		else																	{ return false; }
	}
	// クールタイムが終わっていなけらば無条件で許可無し。
	else { return false; }
}