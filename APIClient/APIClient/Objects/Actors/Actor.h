#pragma once

#define SIZE Collision->GetSize()

class Actor //: public Object
{
public:
	Actor();
	Actor(Vector2 Location);
	virtual ~Actor();

	virtual void Update();

	// 먼저 그려질 정보 - 객체들
	virtual void Render(HDC hdc);

	// 나중에 그려질 정보 - Effect 등
	virtual void AfterRender(HDC hdc) {}

	const virtual Vector2 GetLocation() const { return Location; }
	const bool GetIsActive() const { return IsActive; }

	void AdditionalLocationX(const float& Value) { Location.x += Value; }
	void AdditionalLocationY(const float& Value) { Location.y += Value; }

	void SetFieldTexture(IN BITMAP& Texture) { FieldTexture = &Texture; }
	const RectCollision* GetCollision() const { return Collision; }

protected:
	virtual void OnBegin(RectCollision* Other) {};

private:
	virtual void Init();
	virtual void CollisionSetting() = 0;

protected:
	BITMAP* FieldTexture;

	RectCollision* Collision = nullptr;

	Vector2 Location;

	bool IsActive = true;
};
