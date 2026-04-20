#include "EntityBase.h"

// 初期化内容はここに
void C_EntityBase::Init()
{

}

// 更新内容はここに(描画に使うMatrix(行列)や画像の指定もここ)
void C_EntityBase::Update()
{

}

// 描画内容はここに
void C_EntityBase::Draw()
{

}

// デバッグ画面に表示させるならここに
void C_EntityBase::ImGuiUpdate()
{

}

// Updateに導入する関数
// 操作
void C_EntityBase::MoveControl()
{

}

// 当たり判定のチェック(一対一用)
bool C_EntityBase::HitEntity(Math::Vector2 A_Pos1, Math::Vector2 A_Pos2, Math::Vector2 A_Radius1, Math::Vector2 A_Radius2)
{
	// 三角関数を使って接触しているか調べる。
	// 上下左右の差を求める。
	float X = A_Pos1.x - A_Pos2.x;
	float Y = A_Pos1.y - A_Pos2.y;
	// 求めた差を使ってそれぞれのキャラが直線状でどのくらい離れているか求める。
	float Distance = sqrt(X * X + Y * Y);

	// 求めた直線状の距離とそれぞれの半径を足した値を比較し、数値から接触しているかどうか調べる。
	// 接触しているようならtrue、接触していないのならfalseを返す。
	if (Distance < A_Radius1.x + A_Radius2.x) { return true; }
	else { return false; }
}