#pragma once
#include <memory>

class Input;
class Camera;

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw();
private:
	void DrawGrid();

private:
	int m_frameCount;

	std::shared_ptr<Input> m_pInput;
	std::shared_ptr<Camera> m_pCamera;
};

