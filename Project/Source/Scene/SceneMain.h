#pragma once
#include <memory>

class Input;
class Camera;
class Player;

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

	int m_mapHandle = -1;

	std::shared_ptr<Input> m_pInput;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<Player> m_pPlayer;
};

