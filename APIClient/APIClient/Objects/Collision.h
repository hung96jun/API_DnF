#pragma once
#include "Framework/Framework.h"
#include "Actors/Actor.h"
#include "Utilities/Implement.h"
#include "Enums/ObjectType.h"

struct Vector2;

class Collision;
class RectCollision;
class CircleCollision;

class Character;
class Weapon;

class Collision
{
public:
	Collision() = default;
	Collision(const Vector2 Location) : Location(Location) 
	{
	}
	Collision(const Vector2 Location, const Vector2 Size) : Location(Location), Size(Size) 
	{
	}

	void SetOwner(Actor* Owner) { this->Owner = Owner; }
	Actor* GetOwner() { return Owner; }

	void Update()
	{
		Vector2 location = Owner->GetLocation();
		location += Offset;
		Location = location;
	}

	void SetLocation(const Vector2& Location)
	{
		this->Location = Location;
	}

	void AdditionalLocation(const Vector2& Location)
	{
		this->Location += Location;
	}

	void SetSize(const Vector2& Size)
	{
		this->Size = Size;
	}

	const Vector2 GetLocation() const
	{
		return Location;
	}

	const Vector2 GetSize() const
	{
		return Size;
	}

	virtual const bool OnCollisionOverlap(Vector2& Other) = 0;
	virtual const bool OnCollisionOverlap(RectCollision* Other) = 0;
	virtual const bool OnCollisionOverlap(CircleCollision* Other) = 0;

	virtual void Render(HDC hdc) = 0;
	/**
	* @param	Value	true is hidden
	*/
	void SetHidden(const bool Value) { bHidden = Value; }
	/**
	* Turning on active turns on collision check.
	* @param	Value	true is on Active
	*/
	void SetActive(const bool Value) { bActive = Value; }

	void SetCollisionChannel(const CollisionChannel::Type Type);

	const bool IsHidden() const { return bHidden; }
	const bool IsActive() const { return bActive; }
	const CollisionChannel::Type GetChannel() const { return Channel; }

	void AddFunction(std::function<void(RectCollision*)> Func) { Functor = Func; }

protected:
	std::function<void(RectCollision*)> Functor;

	Vector2 Location = {};
	Vector2 Offset = {};
	Vector2 Size = {};

	CollisionChannel::Type Channel = CollisionChannel::Channel0;

	bool bHidden = true;
	bool bActive = true;

	bool bBindAction = false;

	Actor* Owner = nullptr;
	ObjectType::Type OwnerType = ObjectType::None;
};

class RectCollision : public Collision
{
public:
	RectCollision() = default;
	RectCollision(const Vector2& Location, const Vector2& Size, const CollisionChannel::Type& Channel) : Collision(Location, Size) 
	{
		this->Channel = Channel;
		CollisionManager::Get()->Add(this, Channel);
	}
	RectCollision(const float Left, const float Top, const float Right, const float Bottom);

	virtual const bool OnCollisionOverlap(Vector2& Other) override;
	virtual const bool OnCollisionOverlap(RectCollision* Other) override;
	virtual const bool OnCollisionOverlap(CircleCollision* Other) override;

	virtual void Render(HDC hdc) override;

	const float Left() const { return Location.x - Size.x * 0.5f; }
	const float Right() const { return Location.x + Size.x * 0.5f; }
	const float Top() const { return Location.y - Size.y * 0.5f; }
	const float Bottom() const { return Location.y + Size.y * 0.5f; }
};

class CircleCollision : public Collision
{
public:
	CircleCollision() = default;
	CircleCollision(Vector2 Location, float Radius) : Collision(Location, Vector2(Radius * 2, Radius * 2)) {}
	CircleCollision(Vector2 Location, Vector2 Size) : Collision(Location, Size) 
	{
		if (Size.x == Size.y)
			Radius = Size.x * 0.5f;
	}

	virtual const bool OnCollisionOverlap(Vector2& Other) override;
	virtual const bool OnCollisionOverlap(RectCollision* Other) override;
	virtual const bool OnCollisionOverlap(CircleCollision* Other) override;

	virtual void Render(HDC hdc) override;

private:
	float Radius = 0.0f;
};