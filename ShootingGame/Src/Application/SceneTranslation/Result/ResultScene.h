#pragma once

#include "../SceneManager&State/State.h"

class C_ResultScene :public C_State
{
public:

	C_ResultScene();
	~C_ResultScene() override;

	// 基底クラス(Stateクラス)の関数の内容をここで上書きする
	// 上書きするためには関数の後ろにoverrideと書く

	// 初期化用
	void Init()						override;
	// 更新前に行う更新
	void PreUpdate()			override;
	// 更新処理
	void Update()				override;
	// 更新後に行う更新
	void PostUpdate()			override;
	// 2D描画
	void DrawSprite()			override;
	// デバッグ表示
	void ImGuiUpdate()		override;

private:

	// 解放処理
	void Release();

	// 「Result」の文字用の構造体変数
	S_Entity M_Result;

};