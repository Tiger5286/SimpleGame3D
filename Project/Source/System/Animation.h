#pragma once
#include <string>

class Animation
{
public:
	Animation();
	virtual ~Animation();

	void Init(int modelHandle,std::wstring animName);
	void Update();

	void ChangeAnim(std::wstring animName, float animSpeed = kDefaultAnimSpeed);
private:
	// デフォルトのアニメーションの進行速度
	static constexpr float kDefaultAnimSpeed = 0.5f;

	// アニメーションを行うモデルのハンドル
	int m_modelHandle = -1;

	// アニメーションのハンドル
	int m_currentAnimHandle = -1;
	int m_lastAnimHandle = -1;
	
	// アニメーション管理
	float m_animSpeed = kDefaultAnimSpeed;
	float m_currentAnimTime = 0.0f;
	float m_lastAnimTime = 0.0f;

	// アニメーションの切り替えフレーム数
	int m_animChangeFrame = 0;
};