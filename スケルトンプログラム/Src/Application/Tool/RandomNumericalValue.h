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
		
	}

	// 引数で得た値を最大値としてランダムな値を返す
	int RandomNumericalValue() {};

};
#define RANDOM C_RandomNumericalValue::GetInstance();