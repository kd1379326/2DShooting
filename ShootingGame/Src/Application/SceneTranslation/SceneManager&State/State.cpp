// C_・・・クラス
// M_・・・メンバ
// A_・・・引数
// E_・・・列挙体

// ここの関数の内容は派生クラスで書き換えられる(オーバーライド)から書く必要はないかも。

#include "State.h"

// 初期化
void C_State::Init()
{

}

// 更新前に行いたい更新処理をここに書く。
void C_State::PreUpdate()
{

}

// 更新処理
void C_State::Update()
{

}

// 更新後に行いたい更新処理をここに書く。
void C_State::PostUpdate()
{

}

// 2D描画
void C_State::DrawSprite() 
{

}

// デバッグ表示させたいものをここに書く。
void C_State::ImGuiUpdate()
{

}