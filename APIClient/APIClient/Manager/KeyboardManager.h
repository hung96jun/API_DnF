#pragma once

namespace KeyState
{
	enum Type
	{
		None,
		Down,
		Up,
		Press
	};
}

class KeyboardManager : public Singleton<KeyboardManager>
{
private:
	friend class Singleton;

	static const UINT KEY_MAX = 255;

	KeyboardManager() = default;
	~KeyboardManager() = default;

public:
	void Update();

	bool Down(UINT Value) { return MapState[Value] == KeyState::Down; }
	bool Up(UINT Value) { return MapState[Value] == KeyState::Up; }
	bool Press(UINT Value) { return MapState[Value] == KeyState::Press; }

private:
	BYTE CurState[KEY_MAX] = {};
	BYTE BeforeState[KEY_MAX] = {};
	KeyState::Type MapState[KEY_MAX] = {};
};
