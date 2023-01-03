#pragma once

class Player;
class Keyboard;

class Camera : public Singleton<Camera>
{
private:
	const float MAX_SPEED = 200.0f;

public:
	friend class Camera;

	Camera();
	~Camera();

	void Update();
	void Render(HDC hdc);

	void SetTexture(const BITMAP& Texture) { Bitmap = Texture; }
	void SetRenderTarget(Player* Target) { this->Target = Target; }
	void SetBackgroundRect(RectCollision* RenderRect);

private:
	void SetTargetLocation();
	void SetRenderRectLocation();

	void OnRightClick();
	void EndRightClick();

	void OnLeft();
	void OnRight();
	void OnTop();
	void OnBottom();

private:
	Keyboard* Key = nullptr;

	BITMAP Bitmap;
	RectCollision* Rect = nullptr;
	
	Player* Target = nullptr;
	Vector2 Velocity = {};
	Vector2 Location = {};

	bool bCameraMoveX = false;
	bool bCameraMoveY = false;

	bool bFreeMove = false;
};