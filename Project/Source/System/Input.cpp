#include "Input.h"
#include <cassert>
#include <cmath>

namespace
{
	// スティック入力のデッドゾーンの範囲
	constexpr int kMinStickValue = 3000;
	constexpr int kMaxStickValue = 25000;
}

Input::Input()
{
}

Input::~Input()
{
}

void Input::Update()
{
	m_prevPadInput = m_nowPadInput;

	GetJoypadXInputState(DX_INPUT_PAD1, &m_nowPadInput);
}

bool Input::IsPressed(int button)
{
	return m_nowPadInput.Buttons[button];
}

bool Input::IsTriggerd(int button)
{
	return m_nowPadInput.Buttons[button] && !m_prevPadInput.Buttons[button];
}

Vector3 Input::GetStickInput(LR lr)
{
	Vector3 stick;
	if (lr == LR::Left)
	{
		stick.x = m_nowPadInput.ThumbLX;
		stick.y = m_nowPadInput.ThumbLY;
		stick = ConvertStickInput(stick);
	}
	else if (lr == LR::Right)
	{
		stick.x = m_nowPadInput.ThumbRX;
		stick.y = m_nowPadInput.ThumbRY;
		stick = ConvertStickInput(stick);
	}
	return stick;
}

float Input::GetTriggerInput(LR lr)
{
	if (lr == LR::Left)
	{
		return ConvertTriggerInput(m_nowPadInput.LeftTrigger);
	}
	else if (lr == LR::Right)
	{
		return ConvertTriggerInput(m_nowPadInput.RightTrigger);
	}
	return 0;
}

Vector3 Input::ConvertStickInput(Vector3 stick)
{
	// スティック入力のデッドゾーンを設定
	// -3000~3000の範囲を0とする
	if (stick.x > -kMinStickValue && stick.x < kMinStickValue) stick.x = 0.0f;
	if (stick.y > -kMinStickValue && stick.y < kMinStickValue) stick.y = 0.0f;
	// 25000を超える入力は25000として扱う
	if (stick.x > kMaxStickValue) stick.x = kMaxStickValue;
	if (stick.y > kMaxStickValue) stick.y = kMaxStickValue;
	// -25000未満の入力は-25000として扱う
	if (stick.x < -kMaxStickValue) stick.x = -kMaxStickValue;
	if (stick.y < -kMaxStickValue) stick.y = -kMaxStickValue;

	// -25000~25000の範囲を-1.0~1.0の範囲に変換する

	stick.x = stick.x / kMaxStickValue;
	stick.y = stick.y / kMaxStickValue;

	return stick;
}

float Input::ConvertTriggerInput(unsigned char trigger)
{
	return trigger / 255.0f;
}
