#pragma once

#define FIRST_ATTACK	static_cast<int>(Attack1)
#define LAST_ATTACK		static_cast<int>(Attack3)

class Weapon;

class Player : public Character
{
private:
	const float JUMP_POWER = 800.0f;
	const float GRAVITY = 2000.0f;
	const float Accel_SPEED = 1.7f;
	

	enum CharacterState
	{
		Idle = 0,
		Move = 1,
		Jump = 2,
		Attack1 = 3,
		Attack2 = 4,
		Attack3 = 5,
		Smash = 6,
	};

public:
	Player();
	Player(Vector2 Location);
	~Player();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

protected:
	virtual void OnBegin(RectCollision* Other) override;
	void GetGravity();
	
private:
	void InputKey();
	virtual void Init() override;

	void MoveInput();

	void AnimationSetting();
	void AnimStateSetting();

	void KeyboardSetting();
	void CollisionSetting();

	void AnimationPlay();

	//////////////////////////////////////////////////////////////////////////////
	/// Bind key function
	//////////////////////////////////////////////////////////////////////////////
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void ReleaseMoveHorizontal();
	void ReleaseMoveVertiacal();
	
	void OnAttacking();
	void OnSmashing();
	void OnJump();

	void EndAttacking();
	//////////////////////////////////////////////////////////////////////////////

	void SaveAttacking();
	
private:
	//Weapon* weapon = nullptr;
	Keyboard* Key = nullptr;
	//TestKeyboard* Key = nullptr;
	Animation* Anim = nullptr;

	Vector2 Size = {};
	Vector2 Velocity = {};
	Vector2 TempLocation = {};

	float AccelMagnifi = 1.0f;
	bool bJump = false;

	CharacterState CurState = CharacterState::Idle;
	CharacterState BeforeState = CharacterState::Idle;

	bool IsChangeState = true;
	bool IsMove = true;
	bool bSaveCombo = false;
	bool IsAttack = false;

	UINT AttackCombo = 0;
};