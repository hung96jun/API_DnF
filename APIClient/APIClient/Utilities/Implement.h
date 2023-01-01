#pragma once

#include "Objects/Actors/Actor.h"

// std::function을 사용해서 함수 객체로 만든다음에 사용

//template<typename T>
//class Implement
//{
//public:
//	Implement() = default;
//	Implement(T* Object, void(T::* Func)(Actor*)) : Object(Object), Function(Func) {}
//
//	void operator()(void(T::* Func)(Actor*))
//	{
//		(Object->*Function)(Object);
//	}
//
//	//void CallFunction(Actor* Object)
//	//{
//	//	(Object->*Function)(Object);
//	//}
//
//private:
//	void (T::* Function)(Actor*);
//	T* Object;
//};

//template<typename T>
//class Implement
//{
//public:
//	Implement() = default;
//	Implement(T* Object, void(T::* Func)(const RectCollision&), RectCollision* Target) : Object(Object), Function(Func), Target(Target) {}
//
//	void operator()(void(T::* Func)(const RectCollision&))
//	{
//		(Object->*Function)(Target);
//	}
//
//	//void CallFunction(Actor* Object)
//	//{
//	//	(Object->*Function)(Object);
//	//}
//
//private:
//	void (T::* Function)(const RectCollision&);
//	T* Object;
//	RectCollision* Target;
//};

//template<typename T>
//class Implement1
//{
//public:
//	Implement() = default;
//	Implement(void(T::* Func)(RectCollision*))
//	{
//		Function = Func;
//	}
//
//	//void operator()(void(T::* Func)(const RectCollision&))
//	//{
//	//	(Object->*Function)(Target);
//	//}
//
//	//void CallFunction(Actor* Object)
//	//{
//	//	(Object->*Function)(Object);
//	//}
//
//private:
//	void (T::* Function)(RectCollision*);
//};
//
//template<typename T>
//class TestClass
//{
//public:
//	TestClass() = default;
//	TestClass(void(T::* Func)) : Function(Func){}
//
//private:
//	void(T::* Function);
//};

template<typename T>
class Implement
{
public:
	Implement() = default;
	Implement(T* Object, void(T::* Func)(RectCollision*)) : Object(Object), Function(Func) {}

	void operator()(RectCollision* Obj)
	{
		(Object->*Function)(Obj);
	}

private:
	void (T::* Function)(RectCollision*);
	T* Object;
};

//template<typename T>
//class Implement
//{
//public:
//	Implement() = default;
//	Implement(T* Object, void(T::* Func)(RectCollision*), RectCollision* Target) : Object(Object), Function(Func), Target(Target) {}
//
//	void operator()(void(T::* Func)(RectCollision*))
//	{
//		(Object->*Function)(Target);
//	}
//
//	//void CallFunction(Actor* Object)
//	//{
//	//	(Object->*Function)(Object);
//	//}
//
//private:
//	void (T::* Function)(RectCollision*);
//	T* Object;
//	RectCollision* Target;
//};