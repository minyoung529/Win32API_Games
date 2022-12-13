#pragma once
#include "Object.h"

class Shader;
class Texture;

enum
{
	MATERIAL_ARG_COUNT = 4,
};

struct MaterialParams
{
	MaterialParams()
	{
		for (uint8 i = 0; i < MATERIAL_ARG_COUNT; i++)
		{
			SetInt(i, 0);
			SetFloat(i, 0.0f);
			SetTexOn(i, 0);
		}
	}

	void SetInt(uint8 index, int32 value) { intParams[index] = value; }
	void SetFloat(uint8 index, float value) { floatParams[index] = value; }
	void SetTexOn(uint8 index, int32 value) { texOnParams[index] = value; }
	void SetVec2(uint8 index, Vec2 value) { vec2Params[index] = value; }
	void SetVec4(uint8 index, Vec4 value) { vec4Params[index] = value; }

	array<int32, MATERIAL_ARG_COUNT> intParams;
	array<float, MATERIAL_ARG_COUNT> floatParams;
	array<int32, MATERIAL_ARG_COUNT> texOnParams;
	array<Vec2, MATERIAL_ARG_COUNT> vec2Params;
	array<Vec4, MATERIAL_ARG_COUNT> vec4Params;
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
	void SetTexture(uint8 index, shared_ptr<Texture> texture)
	{
		m_textures[index] = texture;
		m_params.SetTexOn(index, (texture == nullptr ? 0 : 1));
	}
	void SetVec2(uint8 index, Vec2 value) { m_params.SetVec2(index, value); }
	void SetVec4(uint8 index, Vec4 value) { m_params.SetVec4(index, value); }


public:
	void PushData();

private:
	MaterialParams m_params;
	shared_ptr<Shader> m_shader;
	array<shared_ptr<Texture>, MATERIAL_ARG_COUNT> m_textures;
};

