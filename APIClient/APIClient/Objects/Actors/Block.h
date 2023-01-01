#pragma once

class Block : public Actor
{
public:
	Block();
	~Block();

	virtual void Render(HDC hdc) override;

	void Init();

protected:
	virtual void OnBegin(RectCollision* Other) override;

private:
	HDC hdc = nullptr;
};
