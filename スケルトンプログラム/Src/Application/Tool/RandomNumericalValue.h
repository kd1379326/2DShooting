#pragma once

class C_RandomNumericalValue
{
public:

	// コンストラクタとデストラクタ
	C_RandomNumericalValue() {}
	~C_RandomNumericalValue() {}

	// このクラスのインスタンスを渡す関数
	static C_RandomNumericalValue& GetInstance()
	{
		static C_RandomNumericalValue Instance;
		return Instance;
	}

	// 引数で得た値を最大値としてランダムな値を返す
	int RandomNumericalValue(int A_MaximumValue)
	{
		return rand() % (A_MaximumValue + 1);
	}

};
#define RANDOM C_RandomNumericalValue::GetInstance();