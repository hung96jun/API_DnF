#pragma once

class Scene;
class TimerManager;
class KeyboardManager;

class GameManager : public Singleton<GameManager>
{
private:
	friend Singleton;

	GameManager();
	~GameManager();

public:
	void Init();

	void Update(); 
	void Render();

private:
	HDC hdc = nullptr;
	HDC hBackDC = nullptr;
	HBITMAP hBackBitmap = nullptr;

	Scene* scene = nullptr;
};
