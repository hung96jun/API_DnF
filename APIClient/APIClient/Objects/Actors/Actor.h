#pragma once

#define SIZE Collision->GetSize()

class Actor //: public Object
{
public:
	Actor();
	Actor(Vector2 Location);
	virtual ~Actor();

	virtual void Update();

	// ���� �׷��� ���� - ��ü��
	virtual void Render(HDC hdc);

	// ���߿� �׷��� ���� - Effect ��
	virtual void AfterRender(HDC hdc) {}

	const Vector2 GetLocation() const { return Location; }
	const bool GetIsActive() const { return IsActive; }

	void AdditionalLocationX(const float& Value) { Location.x += Value; }
	void AdditionalLocationY(const float& Value) { Location.y += Value; }

protected:
	virtual void OnBegin(RectCollision* Other) = 0;

private:
	virtual void Init();

protected:
	RectCollision* Collision = nullptr;

	Vector2 Location;

	bool IsActive = true;
};
