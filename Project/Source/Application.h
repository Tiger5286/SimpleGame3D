#pragma once
class Application
{
public:
	static Application& GetInstance();
	virtual ~Application() = default;

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
private:
	Application() = default;

public:
	bool Init();
	void Run();
	void Terminate();

	void RequestExit() { m_isRequestExit = true; }

private:
	bool m_isRequestExit = false;
};

