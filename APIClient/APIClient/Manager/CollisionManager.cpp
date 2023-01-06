#include "Framework/Framework.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
	for (map<CollisionChannel::Type, std::vector<RectCollision*>>::iterator it = Collisions.begin(); it != Collisions.end(); it++)
	{
		for (RectCollision* collision : it->second)
		{
			if (collision != nullptr)
				delete collision;

			collision = nullptr;
		}
	}
}

void CollisionManager::CreateCollision(OUT RectCollision*& Collision, IN CollisionChannel::Type Channel)
{
	Collision = new RectCollision();
	Collision->SetCollisionChannel(Channel);

	Collisions[Channel].push_back(Collision);
}

void CollisionManager::Update()
{
	std::vector<RectCollision*> attackers;
	std::vector<RectCollision*> victims;

	for (std::pair<CollisionChannel::Type, std::vector<CollisionChannel::Type>> set : CrashSettings)
	{
		attackers = Collisions[set.first];

		for (CollisionChannel::Type type : set.second)
		{
			if(victims.size() == 0)
				victims = Collisions[type];
			
			for (RectCollision* collision : Collisions[type])
			{
				victims.push_back(collision);
			}
		}

		CollisionCheck(attackers, victims);
	}

	//for (CrashRelation crash : CrashSettings)
	//{
	//	std::vector<RectCollision*> attacker = Collisions[crash.Attacker];
	//	std::vector<RectCollision*> victim = Collisions[crash.Victim];
	//
	//	CollisionCheck(attacker, victim);
	//}
}

void CollisionManager::Add(RectCollision* Collision, CollisionChannel::Type Channel)
{
	if (Collision == nullptr) return;

	if (Collisions.count(Channel) == false)
		++Index;

	Collisions[Channel].push_back(Collision);
}

void CollisionManager::CrashChannelSetting(const CollisionChannel::Type AtcCh, const CollisionChannel::Type VicCh)
{
	//CrashRelation set;
	//set.Attacker = AtcCh;
	//set.Victim = VicCh;

	//CrashSettings.push_back(set);
	CrashSettings[AtcCh].push_back(VicCh);
}

void CollisionManager::ChangeCollisionChannel(RectCollision* Collision, CollisionChannel::Type ChangeCh)
{
	CollisionChannel::Type curCh = Collision->GetChannel();
	std::vector<RectCollision*> collisions = Collisions[curCh];
	
	RectCollision* collision = nullptr;
	int index = 0;
	
	for (int i = 0; i < collisions.size(); ++i)
	{
		if (collisions[i] == Collision)
		{
			collision = collisions[i];
			index = i;

			break;
		}
	}
	
	if (collision == nullptr) return;
	
	Collisions[curCh].erase(Collisions[curCh].begin() + index);
	Collision->SetCollisionChannel(ChangeCh);
	Collisions[ChangeCh].push_back(Collision);
}

void CollisionManager::CollisionCheck(std::vector<RectCollision*> Collisions1, std::vector<RectCollision*> Collisions2)
{
	for (RectCollision* attacker : Collisions1)
	{
		if (attacker->IsActive() == false) continue;

		for (RectCollision* victim : Collisions2)
		{
			attacker->OnCollisionOverlap(victim);
			victim->OnCollisionOverlap(attacker);
		}
	}
}

