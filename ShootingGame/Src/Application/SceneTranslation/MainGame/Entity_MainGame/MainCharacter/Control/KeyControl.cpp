#include "KeyControl.h"

#include "../../../../../Scene.h"

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

	// 座標が画面端を超えた場合、端の座標と半径を計算して画面内に納まるよう固定する。
	if ((A_Position.y + A_Radius.y) > SCENE.Getter_ScreenSize_Top())			{ A_Position.y = (SCENE.Getter_ScreenSize_Top()		  - A_Radius.y); }
	if ((A_Position.x -  A_Radius.x) < SCENE.Getter_ScreenSize_Left())			{ A_Position.x = (SCENE.Getter_ScreenSize_Left()		 + A_Radius.x); }
	if ((A_Position.y -  A_Radius.y) < SCENE.Getter_ScreenSize_Bottom())	{ A_Position.y = (SCENE.Getter_ScreenSize_Bottom()	 + A_Radius.y); }
	if ((A_Position.x + A_Radius.x) > SCENE.Getter_ScreenSize_Right())		{ A_Position.x = (SCENE.Getter_ScreenSize_Right()	  - A_Radius.x); }
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