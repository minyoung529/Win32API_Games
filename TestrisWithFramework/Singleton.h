#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
protected:
	static T* instance;
	Singleton() {}
	virtual ~Singleton() {}

public:
	static T* GetInstance();
	void ReleaseSingleton();
};

#endif

template<typename T>
T* Singleton<T>::instance = nullptr;

template<typename T>
T* Singleton<T>::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new T;
	}

	return instance;
}

template<typename T>
void Singleton<T>::ReleaseSingleton()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}