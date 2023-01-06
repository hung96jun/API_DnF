#pragma once

class Player;
class DogHead;
class Block;

class TestScene : public Scene
{
public:
	TestScene();
	virtual ~TestScene() override;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void AfterRender(HDC hdc) override;

private:
	Background* BackImage = nullptr;
	DogHead* TestDog = nullptr;
	Player* player = nullptr;
<<<<<<< HEAD
=======
	EnergyBall* TestBall = nullptr;
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
	
	//RectCollision* test = nullptr;
	//	Player* test = nullptr;

	RectCollision* Test = nullptr;

	HDC hMemdc;
	BITMAP TestMap;
	HBITMAP hBitmap;

	RectCollision BackRect;
};
