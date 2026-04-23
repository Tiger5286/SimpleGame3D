#pragma once
#include "../Utility/Vector3.h"
#include "../Utility/Sphere.h"
#include "../System/Animation.h"

class Input;

class Player
{
public:
	Player(Input& input);
	virtual ~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	void OnHitModel(MV1_COLL_RESULT_POLY_DIM result);

	Vector3 GetPos() const { return m_pos; }
	const Sphere& GetSphere() const { return m_sphere; }

	void SetCameraAngle(float cameraAngle) { m_cameraAngle = cameraAngle; }

	enum class State
	{
		Idle,
		Run,
		Fall,

		Num
	};

private:
	void Gravity();
	void Move();
	void Jump();

	bool TriggeredChangeState(State state) const;

private:
	Input& m_input;

	int m_modelHandle = -1;

	Animation m_anim;

	Vector3 m_pos;
	Vector3 m_vel;
	Sphere m_sphere;

	bool m_isGround = false;
	float m_angle = 0.0f;

	float m_cameraAngle = 0.0f;

	State m_state = State::Idle;
	State m_prevState = State::Idle;
};