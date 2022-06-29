#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{
protected:
	static T* singleton;
	Singleton(){}
	virtual ~Singleton(){}

public:
	static T* GetSingleton();
	void ReleaseSingleton();
};

template<typename T>
T* Singleton<T>::singleton = nullptr;

template<typename T>
T* Singleton<T>::GetSingleton()
{
	if (singleton == nullptr)
	{
		singleton = new T;
	}

	return singleton;
}

template<typename T>
void Singleton<T>::ReleaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}

#endif // SINGLETON_H


