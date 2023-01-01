#pragma once

enum CollisionChannel::Type;

class Collision;
class RectCollision;
class CircleCollision;

//struct CrashRelation
//{
//	CollisionChannel::Type Attacker;
//	CollisionChannel::Type Victim;
//};

class CollisionManager : public Singleton<CollisionManager>
{
private:
	friend Singleton;

	CollisionManager();
	~CollisionManager();

public:
	void CreateCollision(OUT RectCollision*& Collision, IN CollisionChannel::Type Channel);
	//void CreateCollision(OUT CircleCollision*& Collision, IN CollisionChannel::Type Channel);

	void Update();

	void Add(RectCollision* Collision, CollisionChannel::Type Channel);
	//void Add(CircleCollision* Collision, CollisionChannel::Type Channel);

	void CrashChannelSetting(const CollisionChannel::Type AtcCh, const CollisionChannel::Type VicCh);

	void ChangeCollisionChannel(RectCollision* Collision, CollisionChannel::Type ChangeCh);

private:
	void CollisionCheck(std::vector<RectCollision*> Collisions1, std::vector<RectCollision*> Collisions2);

private:
	int Index = -1;
	
	//std::vector<CrashRelation> CrashSettings;
	std::map<CollisionChannel::Type, std::vector<CollisionChannel::Type>> CrashSettings;
	std::map<CollisionChannel::Type, std::vector<RectCollision*>> Collisions;
};
