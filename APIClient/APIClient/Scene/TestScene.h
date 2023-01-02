#pragma once

class Player;
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
	Player* player = nullptr;
	//RectCollision* test = nullptr;
	Player* test = nullptr;


	HDC hMemdc;
	HBITMAP hBitmap;
};
