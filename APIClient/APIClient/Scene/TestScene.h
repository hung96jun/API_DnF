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
	EnergyBall* TestBall = nullptr;
	
	//RectCollision* test = nullptr;
	//	Player* test = nullptr;

	RectCollision* Test = nullptr;

	HDC hMemdc;
	BITMAP TestMap;
	HBITMAP hBitmap;

	RectCollision BackRect;
};
