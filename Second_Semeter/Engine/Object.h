#pragma once

enum class OBJECT_TYPE : uint8
{
	NONE,
	GAMEOBJECT,
	MATERIAL,
	MESH,
	SHADER,
	TEXTURE,
	COMPONENT,

	END
};

enum
{
	OBJECT_TYPE_COUNT = static_cast<uint8>(OBJECT_TYPE::END)
};

class Object
{
public:
	Object(OBJECT_TYPE type);
	virtual ~Object();

public:
	OBJECT_TYPE GetType() { return m_objectType; }
	const wstring& GetName() { return m_name; }
	void SetName(const wstring& str) { m_name = str; }

protected:
	friend class Resources;
	virtual void Load(const wstring& path) {}
	virtual void Save(const wstring& path) {}

private:
	OBJECT_TYPE m_objectType = OBJECT_TYPE::NONE;
	wstring m_name;

};

