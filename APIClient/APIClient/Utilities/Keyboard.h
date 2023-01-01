#pragma once

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	void Update();

	void Add(KeyValue::Type Type, std::function<void()> function);
	void ChangeKey(KeyValue::Type Type, int Key);

private:
	std::map<KeyValue::Type, int> KeySet;
	std::map<KeyValue::Type, std::function<void()>> FuncSet;
};
