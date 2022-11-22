#pragma once
#include "Object.h"

class Shader;
class Texture;

enum
{
	MATERIAL_INT_COUNT = 5,
	MATERIAL_FLOAT_COUNT = 5,
	MATERIAL_TEXTURE_COUNT = 5,
};

struct MaterialParams
{
	void SetInt(uint8 index, int32 value) { intParams[index] = value; }
	void SetFloat(uint8 index, float value) { floatParams[index] = value; }

	array<int32, MATERIAL_INT_COUNT> intParams;
	array<float, MATERIAL_FLOAT_COUNT> floatParams;
};

class Material : public Object
{
public:
	Material();
	virtual ~Material();

public:
	shared_ptr<Shader> GetShader() { return m_shader; }
	
	void SetShader(shared_ptr<Shader> shader) { m_shader = shader; }
	void SetInt(uint8 index, int32 value) { m_params.SetInt(index, value); }
	void SetFloat(uint8 index, float value) { m_params.SetFloat(index, value); }
	void SetTexture(uint8 index, shared_ptr<Texture> texture) { m_textures[index] = texture; }

public:
	void PushData();

private:
	MaterialParams m_params;
	shared_ptr<Shader> m_shader;
	array<shared_ptr<Texture>, MATERIAL_TEXTURE_COUNT> m_textures;
};

