#include "HitJudgment.h"

bool C_HitJudgment::HitJudgment(Math::Vector2 A_Position1, Math::Vector2 A_Position2, Math::Vector2 A_Radius1, Math::Vector2 A_Radius2)
{
	// 三角関数を使って接触しているか調べる。
// 上下左右の差を求める。
	float X = A_Position1.x - A_Position2.x;
	float Y = A_Position1.y - A_Position2.y;
	// 求めた差を使ってそれぞれのキャラが直線状でどのくらい離れているか求める。
	float Distance = sqrt(X * X + Y * Y);

	// 求めた直線状の距離とそれぞれの半径を足した値を比較し、数値から接触しているかどうか調べる。
	// 接触しているようならtrue、接触していないのならfalseを返す。
	if (Distance < A_Radius1.x + A_Radius2.x) { return true; }
	else { return false; }
}