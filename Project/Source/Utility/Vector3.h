#pragma once
#include "Dxlib.h"

/// <summary>
/// 3次元ベクトルを表すクラス
/// </summary>
class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	// ベクトルの成分
	float x, y, z;

	// DxLib用のベクトルに変換して返す
	VECTOR ToDxLib() const;

	// ベクトルの要素を描画する
	void Draw(int x,int y) const;

	// ベクトルの大きさの二乗を返す
	float SquaredLength() const;
	// ベクトルの大きさを返す
	float Length() const;

	// 自身のベクトルを正規化する
	void Normalize();
	// 正規化されたベクトルを返す
	Vector3 Normalized() const;

	// ベクトルの内積を返す
	float Dot(const Vector3& v) const;
	// ベクトルの外積を返す
	Vector3 Cross(const Vector3& v) const;

	// ベクトルの線形補間をする
	void Lerp(const Vector3& v, float t);

	// 反転したベクトルを返す
	Vector3 operator-() const;
	// ベクトルの足し算
	Vector3 operator+(const Vector3& v) const;
	void operator+=(const Vector3& v);
	// ベクトルの引き算
	Vector3 operator-(const Vector3& v) const;
	void operator-=(const Vector3& v);
	// ベクトルの掛け算
	Vector3 operator*(float s) const;
	void operator*=(float s);

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;
};

