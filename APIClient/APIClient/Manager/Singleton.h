#pragma once

template <typename T>
class Singleton
{
public:
	static T* Get()
	{
		if (instance == NULL)
			instance = new T();

		return instance;
	}

	static void Destory()
	{
		if (instance != NULL)
			delete instance;

		instance = NULL;
	}

private:
	static T* instance;
};

template <typename T>
T* Singleton<T>::instance = NULL;