#include "Framework/Framework.h"
#include "Actors/Weapon/Weapon.h"


RectCollision::RectCollision(const float Left, const float Top, const float Right, const float Bottom)
{
	Location.x = (Left + Right) * 0.5f;
	Location.y = (Top + Bottom) * 0.5f;

	Size.x = abs(Right - Left);
	Size.y = abs(Bottom - Top);

	CollisionManager::Get()->Add(this, CollisionChannel::Channel0);
}

void RectCollision::SetActive(const bool Value)
{
	HitActors.clear();

	Super::SetActive(Value);
}

const bool RectCollision::OnCollisionOverlap(Vector2& Other)
{
	if (bActive == false) return false;
	
	if (Other.x > Left() && Other.y < Right())
	{
		if (Other.y > Top() && Other.y < Bottom())
		{
			if (bBindAction == true)
				return true;
		}
	}

	return false;
}

const bool RectCollision::OnCollisionOverlap(RectCollision* Other)
{
	if (bActive == false) return false;
	if (Other->bActive == false) return false;

	if (Other->Left() < Right() && Other->Right() > Left())
	{
		if (Other->Top() < Bottom() && Other->Bottom() > Top())
		{
			if (HitActors.size() == 0)
			{
				HitActors.push_back(Other);
			}

			else
			{
				for (RectCollision* actor : HitActors)
				{
					if (Other == actor)
						return false;
				}

				HitActors.push_back(Other);
			}

			if(Functor != nullptr)
				Functor(Other);

			return true;
		}
	}

	return false;
}

const bool RectCollision::OnCollisionOverlap(CircleCollision* Other)
{
	if (bActive == false) return false;

	return false;
}

const void RectCollision::EndCollisionOverlap()
{
	HitActors.clear();
}

void RectCollision::Render(HDC hdc)
{
	if (bHidden) return;

	int left = (int)(Location.x - Size.x * 0.5f);
	int right = (int)(Location.x + Size.x * 0.5f);
	int top = (int)(Location.y - Size.y * 0.5f);
	int bottom = (int)(Location.y + Size.y * 0.5f);

	Rectangle(hdc, left, top, right, bottom);
}

const bool CircleCollision::OnCollisionOverlap(Vector2& Other)
{
	return false;
}

const bool CircleCollision::OnCollisionOverlap(RectCollision* Other)
{
	return false;
}

const bool CircleCollision::OnCollisionOverlap(CircleCollision* Other)
{
	return false;
}

void CircleCollision::Render(HDC hdc)
{
}

void CollisionBase::SetCollisionChannel(const CollisionChannel::Type Type)
{
	CollisionManager::Get()->ChangeCollisionChannel((RectCollision*)this, Type);
	Channel = Type;
}
