#pragma region

class Durahan : public Monster
{
public:
	Durahan();
	virtual ~Durahan();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void FiniteStateMachine() override;

protected:
	virtual void OnBegin(RectCollision* Other) override;

private:
	virtual void Init() override;

	virtual void AnimationSetting() override;
	virtual void AnimStateSetting() override;

	virtual void AnimationPlay() override;

};
