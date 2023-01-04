#pragma once

class ObjectManager : public Singleton< ObjectManager>
{
private:
	friend class Singleton;

	ObjectManager();
	~ObjectManager();

public:
	void Update();
	void Render(HDC hdc);
	void AfterRender(HDC hdc);

	void Add(Actor* Object);
	void SetFieldTexture(IN BITMAP& Texture);

private:
	std::vector<Actor*> Objects;
};