#include "Framework/Framework.h"

#include "TestScene.h"

#include "Objects/Actors/Characters/Player/Player.h"
#include "Objects/Actors/Block.h"

TestScene::TestScene()
{
	player = new Player(Vector2(WIN_CENTER_X, WIN_CENTER_Y));
	//test = new RectCollision(Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(50.0f, 50.0f), CollisionChannel::Channel2);
	//test->SetHidden(false);

	//test = new Player(Vector2(WIN_CENTER_X, WIN_CENTER_Y - 200.0f));

	//CollisionManager::Get()->CrashChannelSetting(CollisionChannel::Channel1, CollisionChannel::Channel2);

	HDC hdc = GetDC(hWnd);
	hMemdc = CreateCompatibleDC(hdc);
	wstring str = L"Resource/Player/Knight/000.bmp";
	hBitmap = (HBITMAP)LoadImage(hInst, str.c_str(), IMAGE_BITMAP, 303, 243, LR_LOADFROMFILE);
	SelectObject(hMemdc, hBitmap);
	ReleaseDC(hWnd, hdc);

	CollisionManager::Get()->CrashChannelSetting(CollisionChannel::Channel3, CollisionChannel::Channel1);
	CollisionManager::Get()->CrashChannelSetting(CollisionChannel::Channel3, CollisionChannel::Channel2);
}

TestScene::~TestScene()
{
	delete player;
	//delete test;
}

void TestScene::Update()
{
	//player->Update();

	ObjectManager::Get()->Update();
	//CollisionManager::Get()->Update();
}

void TestScene::Render(HDC hdc)
{
	//player->Render(hdc);
	//test->Render(hdc);

	ObjectManager::Get()->Render(hdc);

	//bool check = BitBlt(hdc,
	//	WIN_CENTER_X, WIN_CENTER_Y,
	//	303, 243,
	//	hMemdc,
	//	0, 0,
	//	SRCCOPY);
	//
	//wstring str;
	//if (check == true)
	//{
	//	str = L"Success";
	//	TextOut(hdc, WIN_CENTER_X, 0, str.c_str(), str.length());
	//}
	//else
	//{
	//	str = L"Failed";
	//	TextOut(hdc, WIN_CENTER_Y, 0, str.c_str(), str.length());
	//}
}

void TestScene::AfterRender(HDC hdc)
{
}
