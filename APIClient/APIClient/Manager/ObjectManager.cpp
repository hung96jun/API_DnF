#include "Framework/Framework.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	for (Actor* object : Objects)
	{
		if (object != nullptr)
			delete object;

		object = nullptr;
	}
}

void ObjectManager::Update()
{
	for (Actor* object : Objects)
	{
		//if(object-)
		if (object->GetIsActive() == false) continue;
		object->Update();
	}
}

void ObjectManager::Render(HDC hdc)
{
	for (Actor* object : Objects)
	{
		if (object->GetIsActive() == false) continue;
		object->Render(hdc);
	}
}

void ObjectManager::AfterRender(HDC hdc)
{
	for (Actor* object : Objects)
	{
		if (object->GetIsActive() == false) continue;
		object->AfterRender(hdc);
	}
}

void ObjectManager::Add(Actor* Object)
{
	Objects.push_back(Object);
}

void ObjectManager::SetFieldTexture(IN BITMAP& Texture)
{
	for (Actor* object : Objects)
	{
		object->SetFieldTexture(Texture);
	}
}
