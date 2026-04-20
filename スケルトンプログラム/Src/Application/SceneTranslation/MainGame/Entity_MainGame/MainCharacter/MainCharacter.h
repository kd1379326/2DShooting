#pragma once

#include "../Base/EntityBase.h"

class C_MainCharacter :public C_EntityBase
{
public:

	// コンストラクタとデストラクタ
	C_MainCharacter();
	~C_MainCharacter();

	// 初期化内容
	void Init()override;
	// 更新内容
	void Update()override;
	// 描画内容
	void Draw()override;
	// デバッグ画面に表示する内容
	void ImGuiUpdate()override;

	// Updateに導入する関数
	// 操作
	void MoveControl()override;

private:

	S_EntityCharacter M_MainCharacter;

};