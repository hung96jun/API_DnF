#include "Framework/Framework.h"

#include "TestScene.h"

#include "Objects/Actors/Characters/Player/Player.h"
#include "Objects/Actors/Characters/Monster/DogHead.h"
#include "Objects/Actors/Block.h"

TestScene::TestScene()
{
<<<<<<< HEAD
	player = new Player(Vector2(WIN_CENTER_X - 300, WIN_CENTER_Y));
=======
	player = new Player(Vector2(WIN_CENTER_X, WIN_CENTER_Y));
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
	TestDog = new DogHead();
	//test = new RectCollision(Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(50.0f, 50.0f), CollisionChannel::Channel2);
	//test->SetHidden(false);

	//test = new Player(Vector2(WIN_CENTER_X, WIN_CENTER_Y - 200.0f));

	//CollisionManager::Get()->CrashChannelSetting(CollisionChannel::Channel1, CollisionChannel::Channel2);

	//HDC hdc = GetDC(hWnd);
	//hMemdc = CreateCompatibleDC(hdc);
	//wstring str = L"Resource/Background/Dungeon1.bmp";
	//hBitmap = (HBITMAP)LoadImage(hInst, str.c_str(), IMAGE_BITMAP, 1568, 720, LR_LOADFROMFILE);
	//SelectObject(hMemdc, hBitmap);
	//ReleaseDC(hWnd, hdc);
	
	//GetObject(hBitmap, sizeof(BITMAP), &TestMap);
	//BackRect = {};
	//Camera::Get()->SetBackgroundRect(&BackRect);
	//Camera::Get()->SetTexture(TestMap);
	BackImage = new Background(L"Resource/Background/DungeonBackground.bmp", Vector2(1568, 720));
	//player->SetField();
	

	Camera::Get()->SetRenderTarget(player);
	
	CollisionManager::Get()->CrashChannelSetting(CollisionChannel::Channel3, CollisionChannel::Channel1);
	CollisionManager::Get()->CrashChannelSetting(CollisionChannel::Channel3, CollisionChannel::Channel2);

	Test = new RectCollision();
	Test->SetSize(Vector2(TestMap.bmWidth, TestMap.bmHeight - 200));
	Test->SetLocation(Vector2(TestMap.bmWidth * 0.5f, TestMap.bmHeight * 0.5f));

<<<<<<< HEAD
	TestDog->SetTarget(player);
=======
	TestBall = new EnergyBall();
	
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c

	//ObjectManager::Get()->SetFieldTexture(BackImage->GetTexture());
}

TestScene::~TestScene()
{
	delete TestDog;
	delete BackImage;
	delete player;
	delete Test;
	delete TestBall;
}

void TestScene::Update()
{
	//player->Update();

	Camera::Get()->Update();
<<<<<<< HEAD
	//TestBall->Update();
=======
	TestBall->Update();
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
	ObjectManager::Get()->Update();
	//CollisionManager::Get()->Update();
}

void TestScene::Render(HDC hdc)
{
	//player->Render(hdc);
	//test->Render(hdc);

	

	//BitBlt(
	//	hdc,
	//	0, 0,
	//	WIN_WIDTH, WIN_HEIGHT,
	//	hMemdc,
	//	BackRect.Left(), BackRect.Top(),
	//	SRCCOPY
	//);
	BackImage->Render(hdc);
<<<<<<< HEAD
	//TestBall->Render(hdc);
=======
	TestBall->Render(hdc);
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
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
