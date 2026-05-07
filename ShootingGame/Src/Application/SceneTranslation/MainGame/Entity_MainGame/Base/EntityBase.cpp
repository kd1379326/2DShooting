#include "EntityBase.h"

// 初期化内容はここに
void C_EntityBase_MainGame::Init(Math::Vector2 A_Position)
{

}

// 操作関連の更新内容はここに
void C_EntityBase_MainGame::Action()
{

}

// 更新内容はここに(描画に使うMatrix(行列)や画像の指定もここ)
void C_EntityBase_MainGame::Update()
{

}

// 描画内容はここに
void C_EntityBase_MainGame::Draw()
{

}

// デバッグ画面に表示させるならここに
void C_EntityBase_MainGame::ImGuiUpdate()
{

}

// Updateに導入する関数
// 当たり判定のチェック(一対一用)
bool C_EntityBase_MainGame::HitEntity(Math::Vector2 A_Position1, Math::Vector2 A_Position2, Math::Vector2 A_Radius1, Math::Vector2 A_Radius2)
{
	// それぞれのキャラが直線状でどのくらい離れているか求める。(.Length()で離れている距離を算出できる)
	float Distance = (A_Position1 - A_Position2).Length();

	// 求めた直線状の距離とそれぞれの半径を足した値を比較し、数値から接触しているかどうか調べる。
	// 接触しているようならtrue、接触していないのならfalseを返す。
	if (Distance < A_Radius1.x + A_Radius2.x) { return true; }
	else { return false; }
}