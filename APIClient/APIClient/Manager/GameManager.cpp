#include "Framework/Framework.h"
#include "GameManager.h"

#include "Scene/TestScene.h"

GameManager::GameManager()
{
	Init();

	scene = new TestScene();
}

GameManager::~GameManager()
{
	if(scene != nullptr)
		delete scene;
	
	TimerManager::Destory();
	KeyboardManager::Destory();
	CollisionManager::Destory();
	Camera::Destory();
}

void GameManager::Init()
{
	hdc = GetDC(hWnd);

	hBackDC = CreateCompatibleDC(hdc);
	hBackBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
	SelectObject(hBackDC, hBackBitmap);

	KeyboardManager::Get();
	TimerManager::Get();
	CollisionManager::Get();
	ObjectManager::Get();
	Camera::Get();

	SetBkMode(hBackDC, TRANSPARENT);
}

void GameManager::Update()
{
	scene->Update();

	KeyboardManager::Get()->Update();
	TimerManager::Get()->Update();
	CollisionManager::Get()->Update();
}

void GameManager::Render()
{
	//wstring str = L"Width : " + to_wstring(WinSize.x);
	//TextOut(hBackDC, 0, 0, str.c_str(), (int)str.length());
	//str = L"\nHeight : " + to_wstring(WinSize.y);
	//TextOut(hBackDC, 0, 20, str.c_str(), (int)str.length());

	PatBlt(hBackDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS);

	scene->Render(hBackDC);

	bool check = BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		hBackDC, 0, 0, SRCCOPY);
}
