#include "Framework/Framework.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	// default setting, Test virsion
	pair<KeyValue::Type, int> keyPair;
	{
		keyPair.first = KeyValue::Attack;
		keyPair.second = 'X';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Smash;
		keyPair.second = 'Z';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Jump;
		keyPair.second = 'C';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Skill1;
		keyPair.second = 'A';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Skill2;
		keyPair.second = 'S';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Skill3;
		keyPair.second = 'D';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Skill4;
		keyPair.second = 'F';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Skill5;
		keyPair.second = 'G';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Skill6;
		keyPair.second = 'H';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Item1;
		keyPair.second = '1';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Item2;
		keyPair.second = '2';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Item3;
		keyPair.second = '3';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Item4;
		keyPair.second = '4';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Item5;
		keyPair.second = '5';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Itme6;
		keyPair.second = '6';
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Escape;
		keyPair.second = VK_ESCAPE;
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Left;
		keyPair.second = VK_LEFT;
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Right;
		keyPair.second = VK_RIGHT;
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Up;
		keyPair.second = VK_UP;
		KeySet.insert(keyPair);
		keyPair.first = KeyValue::Down;
		keyPair.second = VK_DOWN;
		KeySet.insert(keyPair);
	}
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
	for (pair<KeyValue::Type, int> set : KeySet)
	{
		if (KEY_DOWN(set.second))
		{
			if (FuncSet[set.first] != nullptr)
				FuncSet[set.first]();
		}
	}

	if (KEY_PRESS(KeySet[KeyValue::Up]))
	{
		if (FuncSet[KeyValue::Up] != nullptr)
			FuncSet[KeyValue::Up]();
	}
	if (KEY_PRESS(KeySet[KeyValue::Down]))
	{
		if (FuncSet[KeyValue::Down] != nullptr)
			FuncSet[KeyValue::Down]();
	}
	if (KEY_PRESS(KeySet[KeyValue::Left]))
	{
		if (FuncSet[KeyValue::Left] != nullptr)
			FuncSet[KeyValue::Left]();
	}
	if (KEY_PRESS(KeySet[KeyValue::Right]))
	{
		if (FuncSet[KeyValue::Right] != nullptr)
			FuncSet[KeyValue::Right]();
	}
}

void Keyboard::Add(KeyValue::Type Type, function<void()> function)
{
	FuncSet[Type] = function;
}

void Keyboard::ChangeKey(KeyValue::Type Type, int Key)
{
	KeySet[Type] = Key;
}
