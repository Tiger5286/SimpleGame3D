#pragma once
#include "../../Utility/Sphere.h"

enum class ObjectTag
{
	None,
	Player,
	Enemy,
	Chest,
	Coin,
	Punch,
};

class GameObject
{
public:
	GameObject(float sphereRadius);
	virtual ~GameObject();

	virtual void Init() abstract;
	virtual void End() abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract;

	// 他のオブジェクトと当たったときに呼ばれる関数
	virtual void OnCollision(const GameObject& other) abstract;
	// 他のオブジェクトと当たったときに呼ばれる関数(constでない版、危ないのは承知の上で使う)
	virtual void OnCollision2(GameObject& other) {};

	// Init()より前に実行する
	void SetHandle(int handle);

	Vector3 GetPos() const;

	const Sphere& GetSphere() const { return m_sphere; }

	ObjectTag GetTag() const { return m_tag; }

	bool IsHit() const { return m_isHit; }
	void OnHit() { m_isHit = true; }

protected:
	void Gravity();
	void Resistance();

protected:
	Vector3 m_pos;
	Vector3 m_vel;
	int m_modelHandle = -1;

	Sphere m_sphere;

	ObjectTag m_tag = ObjectTag::None;

	bool m_isHit = false;
};