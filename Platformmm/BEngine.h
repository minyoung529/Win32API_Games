#ifndef	  BENGINE_H
#define	  BENGINE_H

#include "BWindow.h"
#include "BImage.h"
#include "BInput.h"
#include "BSound.h"
#include "SceneManager.h"

class BEngine : public BWindow
{
public:
	BEngine();
	~BEngine();

public:
	virtual void			Startup() override;
	virtual void			MainLoop() override;
	virtual void			Cleanup() override;

	virtual void			_Update(float dt);
	virtual void			_Render(HDC hdc, float dt);

private:
	void					RenderText(UINT fps, float dt);

public:
	virtual void			Init();
	virtual void			Update(float dt);
	virtual void			Render(HDC hdc, float dt);
	virtual void			Release();

private:
	LARGE_INTEGER			m_llPrevCount;
	LARGE_INTEGER			m_llCurCount;
	LARGE_INTEGER			m_llFrequency;

	float					m_fDT;			// �����Ӱ� �ð� ��
	float					m_fAcc;			// 1�� üũ�� ���� ���� �ð� 	
	UINT					m_iCallCount;	// �Լ� ȣ�� Ƚ�� üũ
	UINT					m_iFPS;			// �ʴ� ȣ�� Ƚ��

public:
	BInput					m_InputObject;
	BSound					m_SoundObject;
	CSceneManager*			m_SceneManager;
};
#endif // BENGINE_H