#pragma once

struct KeyInfo
{
	KeyValue::Type Type;
	int KeyValue;
};

namespace InputType
{
	enum Type
	{
		Up,
		Down,
		Press,
	};
}

class TestKeyboard
{
public:
	TestKeyboard();
	~TestKeyboard();

	void Update();

	void AddPressKey(KeyValue::Type Type, std::function<void()> function);
	void AddDownKey(KeyValue::Type Type, std::function<void()> function);
	void AddUpKey(KeyValue::Type Type, std::function<void()> function);
	void ChangeKey(KeyValue::Type Type, int Key);

private:
	void DownKeyUpdate();
	void UpKeyUpdate();
	void PressKeyUpdate();

private:
	//std::map<KeyValue::Type, int> KeySet;
	std::map<InputType::Type, std::vector<KeyInfo>> KeySet;
	std::map<KeyValue::Type, std::function<void()>> DownFuncSet;
	std::map<KeyValue::Type, std::function<void()>> UpFuncSet;
	std::map<KeyValue::Type, std::function<void()>> PressFuncSet;
};
