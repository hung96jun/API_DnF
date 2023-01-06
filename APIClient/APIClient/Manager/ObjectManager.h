#pragma once

class ObjectManager : public Singleton<ObjectManager>
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
<<<<<<< HEAD
	std::vector<Actor*> RenderObjects;
=======
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
};