#include "Control.h"

// このクラスが生成された時に動かしたい機能はここに
C_MainCharacterControl::C_MainCharacterControl()
{
}

// このクラスが削除された時に動かしたい機能はここに
C_MainCharacterControl::~C_MainCharacterControl()
{
}

void C_MainCharacterControl::Update()
{
	// クールタイムが発生した時にのみ減らしていく。
	if (M_NowCoolTime > 0) { M_NowCoolTime--; }
}

// キー入力による操作機能
void C_MainCharacterControl::MoveKeyControl(Math::Vector2& A_Position, Math::Vector2& A_Move)
{
	if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000)) { A_Position.y += A_Move.y; }
	if ((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000)) { A_Position.x -= A_Move.x; }
	if ((GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000)) { A_Position.y -= A_Move.y; }
	if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) { A_Position.x += A_Move.x; }
}

// エンターキーが押されたときに弾を放って良いと合図する
bool C_MainCharacterControl::ShootingPermission()
{
	if (M_NowCoolTime <= 0)
	{
		// キーが押されたら撃つ許可を出し、押されていなければ許可しない。
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)	{ return true; M_NowCoolTime = M_CoolTime; }
		else																	{ return false; }
	}
	// クールタイムが終わっていなけらば無条件で許可無し。
	else { return false; }
}