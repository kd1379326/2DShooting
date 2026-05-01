#pragma once

#include "../SceneManager&State/State.h"

class C_TitleScene :public C_State
{
public:

	C_TitleScene();
	~C_TitleScene()  override;

	// 基底クラス(Stateクラス)の関数の内容をここで上書きする
	// 上書きするためには関数の後ろにoverrideと書く

	// 初期化用
	void Init()					override;
	// 更新前に行う更新
	void PreUpdate()		override;
	// 更新処理
	void Update()			override;
	// 更新後に行う更新
	void PostUpdate()		override;
	// 2D描画
	void DrawSprite()		override;
	// デバッグ表示
	void ImGuiUpdate()	override;

private:

	// 解放処理
	void Release();

	// 「Title」の文字用の構造体変数
	S_Entity M_Title;

};