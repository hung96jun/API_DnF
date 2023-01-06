#pragma once

#define FIRST_ATTACK	static_cast<int>(Attack1_R)
#define LAST_ATTACK		static_cast<int>(Attack3_L)

class Weapon;

class Player : public Character
{
private:
	const float JUMP_POWER = 800.0f;
	const float GRAVITY = 2000.0f;
	const float Accel_SPEED = 1.7f;
	
	enum CharacterState
	{
		Idle_R = 0,
		Idle_L = 1,
		Move_R = 2,
		Move_L = 3,
		Jump_R = 4,
		Jump_L = 5,
		Attack1_R = 6,
		Attack1_L = 7,
		Attack2_R = 8,
		Attack2_L = 9,
		Attack3_R = 10,
		Attack3_L = 11,
		Smash_R = 12,
		Smash_L = 13,
	};

public:
	Player();
	Player(Vector2 Location);
	virtual ~Player() override;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	const Vector2& GetVelocity() { return Velocity; }

	void ControlMoveX(bool Value) { IsMoveX = Value; }
	void ControlMoveY(bool Value) { IsMoveY = Value; }

	void SetLocationX(float X) { this->Location.x = X; }
	void SetLocationY(float Y) { this->Location.y = Y; }

	const bool IsJump() { return bJump; }
	void SetField(BITMAP Field) { this->Field = Field; }

	//void TestFunction();
	//void LaunchCharacter(float DirX, float Height);

	virtual void OnDeath() override;

protected:
	virtual void OnBegin(RectCollision* Other) override;
	void GetGravity();
	//void GetLaunchGravity();
	
private:
	void InputKey();
	virtual void Init() override;

	void MoveInput();

	virtual void AnimationSetting() override;
	virtual void AnimStateSetting() override;

	void KeyboardSetting();
	virtual void CollisionSetting() override;

	virtual void AnimationPlay() override;

	//////////////////////////////////////////////////////////////////////////////
	// Bind key function
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

	void AttackMoveForward();

	void EndAttacking();
	//////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////
	// Animation Bind Function
	//////////////////////////////////////////////////////////////////////////////
	void OnAttackCollision();
	void EndAttackCollision();
	//////////////////////////////////////////////////////////////////////////////

	void SaveAttacking();

private:
	Weapon* Sword = nullptr;
	Keyboard* Key = nullptr;
	BITMAP Field;
	//TestKeyboard* Key = nullptr;
	//Animation* Anim = nullptr;
	
	Vector2 Velocity = {};
	// Before the Jump Location
	Vector2 TempLocation = {};

	float AccelMagnifi = 1.0f;
	bool bJump = false;

	CharacterState CurState = CharacterState::Idle_R;
	CharacterState BeforeState = CharacterState::Idle_R;
	//Direction CurDir = Direction::Right;

	bool IsChangeState = true;
	bool IsMove = true;
	bool IsMoveX = true;
	bool IsMoveY = true;
	bool bSaveCombo = false;
	bool IsAttack = false;

	//bool bLaunch = false;
};