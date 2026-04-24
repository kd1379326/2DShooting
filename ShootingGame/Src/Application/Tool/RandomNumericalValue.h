#pragma once

class C_RandomNumericalValue
{
public:

	// コンストラクタとデストラクタ
	C_RandomNumericalValue() {}
	~C_RandomNumericalValue() {}

	// このクラスのインスタンスを渡す関数
	static C_RandomNumericalValue &GetInstance()
	{
		static C_RandomNumericalValue Instance;
		return Instance;
	}

	// 引数を最大値としてランダムな値を返す
	// 引数：int 最大値
	int RandomNumericalValue(int A_MaximumValue)
	{
		// そのまま与えると最大値が引数-1になる為ランダム値を余りで求める前に+1しておく。
		return rand() % (A_MaximumValue + 1);
	}

	// 第一引数を最大値、第二引数を最小値としてランダムな値を返す
	// 引数：int 最大値, int 最小値
	int RandomNumericalValue(int A_MaximumValue, int A_MinimumValue)
	{
		return rand() % (A_MaximumValue + 1 - A_MinimumValue) + A_MinimumValue;
	}

};
