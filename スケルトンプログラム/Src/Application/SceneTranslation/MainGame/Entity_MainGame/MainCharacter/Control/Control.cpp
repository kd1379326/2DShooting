#include "Control.h"

// このクラスが生成された時に動かしたい機能はここに
C_MainCharacterControl::C_MainCharacterControl()
{
}

// このクラスが削除された時に動かしたい機能はここに
C_MainCharacterControl::~C_MainCharacterControl()
{
}

// キー入力による操作機能
void C_MainCharacterControl::MoveKeyControl(Math::Vector2& A_Position, Math::Vector2& A_Move)
{
	if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState(VK_UP) & 0x8000)) { A_Position.y += A_Move.y; }
	if ((GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000)) { A_Position.x -= A_Move.x; }
	if ((GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState(VK_DOWN) & 0x8000)) { A_Position.y -= A_Move.y; }
	if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) { A_Position.x += A_Move.x; }
}
