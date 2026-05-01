#pragma once

#include "../SceneManager&State/State.h"

class C_ResultScene :public C_State
{
public:

	C_ResultScene();
	~C_ResultScene() override;

	// 基底クラス(Stateクラス)の関数の内容をここで上書きする
	// 上書きするためには関数の後ろにoverrideと書く

	// 初期化
	void Init()override;
	// 更新
	void Update()override;
	// 描画
	void Draw()override;
	// デバッグ画面
	void ImGuiUpdate()override;

private:

	// 解放処理
	void Release();

	// 「Result」の文字用の構造体変数
	S_Entity M_Result;

};