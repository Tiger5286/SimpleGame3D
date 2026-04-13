#pragma once
#include "DxLib.h"
#include "../Utility/Vector3.h"

enum class LR
{
	Left,
	Right
};

class Input
{
public:
	Input();
	virtual ~Input();

	void Update();

	/// <summary>
	/// ボタンが押されているかどうか取得する(引数にはXINPUT_BUTTON定義を使用する)
	/// </summary>
	/// <param name="button">取得したいボタン</param>
	/// <returns>押されているかどうか</returns>
	bool IsPressed(int button);

	/// <summary>
	/// ボタンが押された瞬間を取得する(引数にはXINPUT_BUTTON定義を使用する)
	/// </summary>
	/// <param name="button">取得したいボタン</param>
	/// <returns>押されたかどうか</returns>
	bool IsTriggerd(int button);

	/// <summary>
	/// スティック入力を取得する
	/// </summary>
	/// <param name="lr">左右どちらの入力を取得するか</param>
	/// <returns>スティック入力値</returns>
	Vector3 GetStickInput(LR lr);

	/// <summary>
	/// トリガー入力を取得する
	/// </summary>
	/// <param name="lr">左右どちらの入力を取得するか</param>
	/// <returns>トリガー入力値</returns>
	float GetTriggerInput(LR lr);

private:
	/// <summary>
	/// 生スティック入力を-1.0~1.0の扱いやすい形にする
	/// </summary>
	/// <param name="stick">生スティック入力</param>
	/// <returns>加工後のスティック入力値</returns>
	Vector3 ConvertStickInput(Vector3 stick);

	/// <summary>
	/// 生トリガー入力を0.0~1.0の扱いやすい形にする
	/// </summary>
	/// <param name="trigger">生トリガー入力</param>
	/// <returns>加工後のトリガー入力値</returns>
	float ConvertTriggerInput(unsigned char trigger);

private:
	XINPUT_STATE m_nowPadInput;
	XINPUT_STATE m_prevPadInput;
};