// C_・・・クラス
// M_・・・メンバ
// A_・・・引数
// E_・・・列挙体
// S_・・・構造体
// P_・・・ポインター
// F_・・・フラグ

#pragma once

class Scene
{
private:

	// 画面の端の座標
		// 上
		static const int M_ScreenSize_Top		= 360;		
		// 下
		static const int M_ScreenSize_Bottom = -360 + 128;	
		// 右
		static const int M_ScreenSize_Right	= 640;		
		// 左
		static const int M_ScreenSize_Left		= -640;	

		static const int M_BackTexMAX = 4;
		KdTexture M_BackTex[M_BackTexMAX];
		Math::Vector2 M_BackPos[M_BackTexMAX];
		Math::Matrix M_BackMat[M_BackTexMAX];

		static const int M_StarNumMAX = 3;
		static const int M_StarTexMAX = 3;
		KdTexture M_StarTex[M_StarNumMAX][M_StarTexMAX];
		Math::Vector2 M_StarPos[M_StarNumMAX][M_StarTexMAX];
		Math::Matrix M_StarMat[M_StarNumMAX][M_StarTexMAX];

	int M_MainCharaHP = 7;

	int M_EnemyAliveNum = 0;

	bool M_MainCharaAlive = true;

	bool M_MainCharaDelete = false;

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	// ゲッター
	// 画面端の座標を返す。
		// 上
		int Getter_ScreenSize_Top()			{ return M_ScreenSize_Top; }
		// 下
		int Getter_ScreenSize_Bottom()		{ return M_ScreenSize_Bottom; }	
		// 右
		int Getter_ScreenSize_Right()			{ return M_ScreenSize_Right; }		
		// 左
		int Getter_ScreenSize_Left()			{ return M_ScreenSize_Left; }


		int Getter_MainCharaHP() { return M_MainCharaHP; }
		int Getter_EnemyAliveNum() { return M_EnemyAliveNum; }
		bool Getter_MainCharaAlive() { return M_MainCharaAlive; }
		bool Getter_MainCharaDelete() { return M_MainCharaDelete; }

		void Setter_MainCharaHP(int A_HP) { M_MainCharaHP = A_HP; }
		void Setter_EnemyAliveNum(int A_AliveNum) { M_EnemyAliveNum = A_AliveNum; }
		void Setter_MainCharaAlive(bool A_Alive) { M_MainCharaAlive = A_Alive; }
		void Setter_MainCharaDelete(bool A_Delete) { M_MainCharaDelete = A_Delete; }

private:

	Scene() {}

public:
	static Scene& Instance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::Instance()
